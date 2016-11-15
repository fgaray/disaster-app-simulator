#include "Network3G.hpp"

#include <algorithm>



Network3G::Network3G(std::initializer_list<handle<Device>> dv, std::initializer_list<handle<Antena>> al): Process("Network"){
  for (auto ant : al){
    this->antenas.insert({ant->getId(), ant});
  }

  for (auto device : dv){
    this->devices.insert({device->getId(), device});
    //Para cada device, encontrar antena
    std::vector<std::tuple<handle<Antena>, double>> dist_vect;
    for (auto ant = this->antenas.begin(); ant != this->antenas.end(); ++ant ){
      double dev_dist = ant->second->distancia(device);

      if((*ant).second->getRadio() > dev_dist){
        dist_vect.push_back(std::make_tuple((*ant).second, dev_dist));
      }
    }
    std::sort(dist_vect.begin(), dist_vect.end(), [](auto &left, auto &right) {
        return std::get<1>(left) < std::get<1>(right);
        });

    this->devices_antenas.insert({device->getId(), std::get<0>(dist_vect.at(0))});
  }

}

Id Network3G::buscarNuevaAnt(handle<Device> device){
  std::vector<std::tuple<handle<Antena>, double>> dist_vect;
  for (auto ant = this->antenas.begin(); ant != this->antenas.end(); ++ant ){
    double dev_dist = ant->second->distancia(device);

    if((*ant).second->getRadio() > dev_dist){
      dist_vect.push_back(std::make_tuple((*ant).second, dev_dist));
    }
  }
  std::sort(dist_vect.begin(), dist_vect.end(), [](auto &left, auto &right) {
      return std::get<1>(left) < std::get<1>(right);
      });

  this->devices_antenas.insert({device->getId(), std::get<0>(dist_vect.at(0))});
  return std::get<0>(dist_vect.at(0))->getId();
}

void Network3G::enviarMensajeHaciaMD(Id hacia, MessageMD m){
  /*
  sacar id 
  buscar id en map devices_antenas
  mientras enviar mensaje antena == False
    calcular nueva antena
    actualizar map devices_antenas
  */
  std::stringstream ss2;
  ss2 << "Recibido un mensaje, buscando antena para dispositivo ";
  ss2 << hacia;
  this->traza->puntoRed3G(time(), ss2);

  auto found_index = this->devices_antenas.find(hacia);
  //auto found = this->translation_table_tmp.find(name);
  assert(found_index != this->devices_antenas.end());
  //assert(found != this->translation_table_tmp.end());

  Id next_antena = (*found_index).second->getId();

  std::stringstream ss;
  ss << "Destino encontrado, enviando a antena";
  ss << next_antena;

  this->traza->puntoRed3G(time(), ss);
  this->enviarMensajeAntena(next_antena, hacia, m);
}

void Network3G::enviarMensajeAntena(Id antena, Id device, MessageMD message){

  // el mensaje es dividido en paquetes que son puestos en un buffer2 de entrada
  // de la red 3g a la espera de ser enviados por la red.

  std::stringstream ss2;
  ss2 << "Recibido un mensaje con destino ";
  ss2 << antena;
  this->traza->puntoRed3G(time(), ss2);

  unsigned int number = 0;
  bool last = false;

  //el mensaje a enviar no puede tener un size cero
  assert(message.getSize() != 0);

  for(unsigned int restante = message.getSize();restante > 0;restante = restante - PACKET_SIZE, number++){
    PacketMD pkt(message, number, last);
    this->input_buffer.push_back(std::make_tuple(antena, device, pkt));
  }

  std::stringstream ss;
  ss << "Mensaje ";
  ss << message.getId();
  ss << " de tamaño ";
  ss << message.getSize();
  ss << " bits fue dividido en ";
  ss << number;
  ss << " paquetes de tamaño ";
  ss << PACKET_SIZE << " bits";
  this->traza->puntoRed3G(time(), ss);

  //deberiamos haber agregado al menos un mensaje
  assert(this->input_buffer.size() != 0);

  std::get<2>(this->input_buffer.at(this->input_buffer.size() - 1));

  this->traza->puntoRed3G(time(), "Volviendo a activar la red");
  this->activate();
}

void Network3G::enviarMensajeHaciaCluster(MessageMD m){
  throw UNDEFINED;
}


std::function<void(MessageMD)> Network3G::getSendCallback(){
  return [this](MessageMD message){
    this->enviarMensajeHaciaCluster(message);
  };
}

std::function<void(std::shared_ptr<Device>)> Network3G::getMoveCallback(){
  throw UNDEFINED;
}

void Network3G::inner_body(){
  while(this->run){
    if(this->current.empty()){
      this->intentarAgregarPaquete();
      //si luego que intentamos agregar más paquetes seguimos sin tener ninguno,
      //entonces ahora si esperamos, en caso contrario tenemos que enviar el
      //paquete por la red
      if(this->current.empty()){
        this->traza->puntoRed3G(time(), "No hay más mensajes por enviar por la red, esperando...");
        this->passivate();
      }
    }else{
      //obtenemos el que tiene menor remaining time, este va a ser nuestro hold
      //y es el que está al principio del heap

      PacketMD p = std::get<2>(this->current.at(0));

      double to_hold = p.getRemainingTime();

      std::stringstream ss;
      ss << "Enviando paquete ";
      ss << p.getNumber();
      ss << " del mensaje ";
      ss << p.getMessage().getId();
      ss << ", vamos a esperar ";
      ss << to_hold;
      this->traza->puntoRed3G(time(), ss);


      //sabemos cuanto esperar, esperamos...
      assert(to_hold != 0);
      hold(to_hold);

      //ahora, a todos los paquetes que están esperando, tenemos que restarle el
      //tiempo a esperar. Dado que a todos les restamos la misma cantidad, la
      //propiedad de heap debería mantenerse

      for(auto &t: this->current){
        std::get<2>(t).restarTiempo(to_hold);
      }
     
      // ahora debemos sacar los elementos del heap current. Si el elemento es
      // final (el ultimo packet) entonces le mandamos el mensaje a la CPU, si
      // no, solamente lo descartamos

      // no podemos borrar directamente aqui ya que estamos usando el iterator,
      // tenemos que guardar los iterators en un puntero y desde el vamos a ir
      // sacando los iterators que hay que eliminar

      std::vector<std::vector<std::tuple<Id, Id, PacketMD>>::iterator> a_eliminar;

      for(auto it = this->current.begin(); it != this->current.end();it++){
        auto tupla = *it;
        PacketMD p = std::get<2>(tupla);
        Id id_antena = std::get<0>(tupla);
        Id id_device = std::get<1>(tupla);

        auto ant = this->antenas.find(id_antena);
        auto dev = this->devices.find(id_device);

        if ((*ant).second->distancia((*dev).second) > (*ant).second->getRadio())
        {
          devices_antenas.erase(id_device);
          Id idnew_antena = buscarNuevaAnt((*dev).second);
          input_buffer.push_back(std::make_tuple(idnew_antena, (*dev).second->getId(), p));
          hold(1); //numero random
          //sacamos el elemento del heap
          a_eliminar.push_back(it);
          //ahora sacamos el mensaje de la tabla hash de manera de permitir
          //que entre otro posible paquete del mismo mensjae
          this->existe.erase(p.getMessage().getId());
        }
        else{
          if(p.getRemainingTime() <= 0){
            //hay que ver si era el final
            if(p.isLast()){
              //era el ultimo, entonces pasamos el mensaje a la CPU
              this->entregarMensaje(id_antena, id_device, p);
            }
            //sacamos el elemento del heap
            a_eliminar.push_back(it);
            //ahora sacamos el mensaje de la tabla hash de manera de permitir
            //que entre otro posible paquete del mismo mensjae
            this->existe.erase(p.getMessage().getId());
          }
        }
      }

      for(auto it: a_eliminar){
        this->current.erase(it);
        std::pop_heap(this->current.begin(), this->current.end());
      }

      this->intentarAgregarPaquete();
    }
  }
}

bool Network3G::redSaturada(){
  unsigned int total = 0;
  for(auto &t: this->current){
    PacketMD p = std::get<2>(t);
    total = total + p.getPacketSize();
  }

  return total > ANCHO_BANDA_INSTANTE_3G;
}

void Network3G::entregarMensaje(Id id_antena, Id id_device, PacketMD p){
  //tenemos que encontrar la CPU a la cual vamos a enviar el mensaje del
  //paquete. Para un mensaje, buscamos en cual de todas las CPUs se encuentra el
  //PE con el ID, si no lo encontramos, entonces en alguna parte estamos mal.

  auto antena = this->antenas.find(id_antena);
  assert(antena != this->antenas.end());

  (*antena).second->recibirMensaje(id_device, p.getMessage());
}


std::function<void(Device*)> Network3G::getCallbackNotificarMovimiento(){
  return [this](Device *d){
    this->notificarMovimientoDevice(d);
  };
}


void Network3G::notificarMovimientoDevice(Device *d){
  throw UNDEFINED;
}


void Network3G::intentarAgregarPaquete(){
  if(!this->input_buffer.empty()){
    if(!this->redSaturada()){
      //intentamos poner un nuevo paquete que no sea parte de los mensajes que
      //ya están en la red

      std::vector<buffer2::iterator> a_eliminar;

      for(auto it = this->input_buffer.begin(); it != this->input_buffer.end(); it++){
        auto t = *it;
        MessageMD m = std::get<2>(t).getMessage();

        auto existe = this->existe.find(m.getId());
        if(existe == this->existe.end()){
          //el mensaje no se encuentra en la red, por lo tanto podemos enviarlo
          this->current.push_back(t);
          std::push_heap(this->current.begin(), this->current.end());
          this->existe.insert({m.getId(), true});
          a_eliminar.push_back(it);
        }
      }
      for(auto it: a_eliminar){
        this->input_buffer.erase(it);
      }
    }else{
      this->traza->puntoRed3G(time(), "La red está llena");
    }
  }else{
    this->traza->puntoRed3G(time(), "La red 3G está vacia");
  }
}


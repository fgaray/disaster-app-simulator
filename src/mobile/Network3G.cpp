#include "Network3G.hpp"

#include <algorithm>
#include "../pe/PEName.hpp"
#include "../pe/MessagePE.hpp"



Network3G::Network3G(std::vector<handle<Device>> dv, std::vector<handle<Antena>> al, std::function<void(PEName, MessagePE)> callback): Process("Network"){
  for (auto ant : al){
    ant->setResponderCallback([callback](MessageMD m){
          MessagePE mpe;
          mpe.setTag();
          callback(PEName::PEPybossa, mpe);
        });

    this->antenas.insert({ant->getId(), ant});
  }


  for (auto device : dv){
    this->devices.insert({device->getId(), device});
    device->setMoveCallback(this->getCallbackNotificarMovimiento());
    device->setSendCallback(this->getSendCallback());
    
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

Id Network3G::buscarNuevaAnt(Device *device){
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


bool Network3G::handover(Id id_device, Id id_antena, buffer2 temporal_buffer){
  
  auto ant = this->antenas.find(id_antena);
  auto dev = this->devices.find(id_device);
   
  //se comprueba si el device sigue o no en la misma antena
  //
  //en caso que ya no este en el radio de la misma antena
  if ((ant*).second->distancia((dev*).second) > (ant*).second->getRadio())
  {
    //Se actualiza el mapa con la nueva antena
    devices_antenas.erase(id_device);
    Id idnew_antena = buscarNuevaAnt((dev*).second);
    //input_buffer.push_back(std::make_tuple(idnew_antena, (dev*).second->getId(), p));
    buffer_rebotados.push_back(std::make_tuple(idnew_antena, (dev*).second->getId(), p));
      
    auto new_ant = this->antenas.find(idnew_antena);
    (new_ant*).second->devices.insert(dev);	  
    //se hace un hold que considera la busqueda de la nueva antena 
    //y el envio del mensaje a la nueva antena
    hold(BUSQUEDA_ANTENA+LATENCIA_RED);
    //se agregan los paquetes a un buffer de rebotados
    
    if

    //this->entregarMensaje(id_antena, id_device, p);
  
    //ahora sacamos el mensaje de la tabla hash de manera de permitir
    //que entre otro posible paquete del mismo mensaje
    return false;
  }
  else
  {
    (ant*).second->devices.insert(dev);	  
    return true;	  
  }
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
  // se crea un buffer temporal de paquetes vector<Id, Id, PacketMD>
  buffer2 temporal_buffer;
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

  //se divide y agrega los paquetes al buffer temporal
  for(unsigned int restante = message.getSize();restante > 0;restante = restante - PACKET_SIZE, number++){
    PacketMD pkt(message, number, last);
    this->temporal_buffer.push_back(std::make_tuple(antena, device, pkt));
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

  // se llama la funcion handover para ver si el device cambio de antena
  asset(this->handover(device, antena, temporal_buffer);
  
  //deberiamos haber agregado al menos un mensaje
  assert(this->buffer_temporal.size() != 0);

  std::get<2>(this->temporal_buffer.at(this->input_buffer.size() - 1)).setLast(true);
  
  auto ant = this->antenas.find(id_antena);
  
  (ant*).second->recibirPaquetes(temporal_buffer);
  //entregarPaquetesAntena(temporal_buffer);
 // this->traza->puntoRed3G(time(), "Volviendo a activar la red");
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

  for(auto d: this->devices){
    d.second->iniciar_mov();
  }



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

        // en caso que el dispositivo ya no se encuentre en la misma antena
        //
        	
        handover(*it, a_eliminar);
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

void Network3G::entregarPaquete(Id id_antena, Id id_device, PacketMD p){
  //tenemos que encontrar la Antena a la cual vamos a enviar el mensaje del
  //paquete. Para un mensaje, buscamos en cual de todas las antenas se encuentra el
  //device con el ID, si no lo encontramos, entonces en alguna parte estamos mal.

  auto antena = this->antenas.find(id_antena);
  assert(antena != this->antenas.end());

  (*antena).second->recibirMessage(id_device, p.getMessage());
}


std::function<void(Device*)> Network3G::getCallbackNotificarMovimiento(){
  return [this](Device *d){
    this->notificarMovimientoDevice(d);
  };
}


void Network3G::notificarMovimientoDevice(Device *d){
  ant->distancia(d);
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


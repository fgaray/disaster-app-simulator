#include "RedTubo.hpp"


RedTubo::RedTubo(std::initializer_list<handle<CPU>> il): Process("RedTubo"){
  for(auto cpu: il){
    cpu->setEnvioMensajeCallback([this](PEName destino, MessagePE message){
        this->enviarMensaje(destino, message);
      });

    for(auto id: cpu->getIdsPEs()){
      this->cpus.insert({id, cpu});
    }

    for(auto t: cpu->getNamesPEs()){
      PEName name;
      Id id;
      std::tie(name, id) = t;
      auto found = this->translation_table_tmp.find(name);
      if(found == this->translation_table_tmp.end()){
        auto v = vector<Id>{id};
        this->translation_table_tmp.insert({name, v});
      }else{
        auto &v = (*found).second;
        v.push_back(id);
      }
    }

    for(auto pair: this->translation_table_tmp){
      auto v = pair.second;
      PEName name = pair.first;
      this->translation_table.insert({name, RoundRobinIterator(v)});
    }
  }

  std::make_heap(this->current.begin(), this->current.end());
}

void RedTubo::enviarMensaje(Id destino, MessagePE message){

  // el mensaje es dividido en paquetes que son puestos en un buffer de entrada
  // de la red tubo a la espera de ser enviados por la red.

  std::stringstream ss2;
  ss2 << "Recibido un mensaje con destino ";
  ss2 << destino;
  this->traza->puntoRedTubo(time(), ss2);

  unsigned int number = 0;
  bool last = false;

  //el mensaje a enviar no puede tener un size cero
  assert(message.getSize() != 0);

  for(unsigned int restante = message.getSize();restante > 0;restante = restante - PACKET_SIZE, number++){
    Packet pkt(message, number, last);
    this->input_buffer.push_back(std::make_tuple(destino, pkt));
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
  this->traza->puntoRedTubo(time(), ss);

  //deberiamos haber agregado al menos un mensaje
  assert(this->input_buffer.size() != 0);

  std::get<1>(this->input_buffer.at(this->input_buffer.size() - 1)).setLast(true);

  this->traza->puntoRedTubo(time(), "Volviendo a activar la red");
  this->activate();
}

void RedTubo::enviarMensaje(PEName name, MessagePE message){
  // Dado que nos preguntaron por el nombre, yo puedo enviar el mensaje a
  // cualquier PE que tenga ese nombre, en caso de que exista más de un PE con
  // ese nombre, entonces se hace round robin sobre el PE.
  //

  if(name == PEName::END){
    // es el mensaje final, no es necesario enviar más mensajes
    std::stringstream ss2;
    ss2 << "Recibido un mensaje final, se termina...";
    this->traza->puntoRedTubo(time(), ss2);
    return;
  }

  std::stringstream ss2;
  ss2 << "Recibido un mensaje, buscando destino hacia ";
  ss2 << peNameToString(name);
  this->traza->puntoRedTubo(time(), ss2);

  auto found_index = this->translation_table.find(name);
  auto found = this->translation_table_tmp.find(name);
  assert(found_index != this->translation_table.end());
  assert(found != this->translation_table_tmp.end());

  size_t next_index = (*found_index).second.getNext();
  Id next = (*found).second.at(next_index);
  message.setDestino(next);

  std::stringstream ss;
  ss << "Destino encontrado, enviando a ";
  ss << next;

  this->traza->puntoRedTubo(time(), ss);
  this->enviarMensaje(next, message);
}


void RedTubo::inner_body(){
  while(this->run){
    if(this->current.empty()){
      this->intentarAgregarPaquete();
      //si luego que intentamos agregar más paquetes seguimos sin tener ninguno,
      //entonces ahora si esperamos, en caso contrario tenemos que enviar el
      //paquete por la red
      if(this->current.empty()){
        this->traza->puntoRedTubo(time(), "No hay más mensajes por enviar por la red, esperando...");
        this->passivate();
      }
    }else{
      //obtenemos el que tiene menor remaining time, este va a ser nuestro hold
      //y es el que está al principio del heap

      Packet p = std::get<1>(this->current.at(0));

      double to_hold = p.getRemainingTime();

      std::stringstream ss;
      ss << "Enviando paquete ";
      ss << p.getNumber();
      ss << " del mensaje ";
      ss << p.getMessage().getId();
      ss << ", vamos a esperar ";
      ss << to_hold;
      this->traza->puntoRedTubo(time(), ss);


      //sabemos cuanto esperar, esperamos...
      assert(to_hold != 0);
      hold(to_hold);

      //ahora, a todos los paquetes que están esperando, tenemos que restarle el
      //tiempo a esperar. Dado que a todos les restamos la misma cantidad, la
      //propiedad de heap debería mantenerse

      for(auto &t: this->current){
        std::get<1>(t).restarTiempo(to_hold);
      }
     
      // ahora debemos sacar los elementos del heap current. Si el elemento es
      // final (el ultimo packet) entonces le mandamos el mensaje a la CPU, si
      // no, solamente lo descartamos

      // no podemos borrar directamente aqui ya que estamos usando el iterator,
      // tenemos que guardar los iterators en un puntero y desde el vamos a ir
      // sacando los iterators que hay que eliminar

      std::vector<std::vector<std::tuple<Id, Packet>>::iterator> a_eliminar;

      for(auto it = this->current.begin(); it != this->current.end();it++){
        auto tupla = *it;
        Packet p = std::get<1>(tupla);
        Id id = std::get<0>(tupla);

        if(p.getRemainingTime() <= 0){
          //hay que ver si era el final
          if(p.isLast()){
            //era el ultimo, entonces pasamos el mensaje a la CPU
            this->entregarMensaje(id, p);
          }
          //sacamos el elemento del heap
          a_eliminar.push_back(it);
          //ahora sacamos el mensaje de la tabla hash de manera de permitir
          //que entre otro posible paquete del mismo mensjae
          this->existe.erase(p.getMessage().getId());
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



bool RedTubo::tuboLleno(){
  unsigned int total = 0;
  for(auto &t: this->current){
    Packet p = std::get<1>(t);
    total = total + p.getPacketSize();
  }

  return total > ANCHO_BANDA_INSTANTE;
}

void RedTubo::intentarAgregarPaquete(){
  if(!this->input_buffer.empty()){
    if(!this->tuboLleno()){
      //intentamos poner un nuevo paquete que no sea parte de los mensajes que
      //ya están en la red

      std::vector<buffer::iterator> a_eliminar;

      for(auto it = this->input_buffer.begin(); it != this->input_buffer.end(); it++){
        auto t = *it;
        MessagePE m = std::get<1>(t).getMessage();

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
      this->traza->puntoRedTubo(time(), "El tubo está lleno");
    }
  }else{
    this->traza->puntoRedTubo(time(), "El buffer de entrada está vacio");
  }
}



void RedTubo::entregarMensaje(Id id, Packet p){
  //tenemos que encontrar la CPU a la cual vamos a enviar el mensaje del
  //paquete. Para un mensaje, buscamos en cual de todas las CPUs se encuentra el
  //PE con el ID, si no lo encontramos, entonces en alguna parte estamos mal.

  auto cpu = this->cpus.find(id);
  assert(cpu != this->cpus.end());

  (*cpu).second->recibirMessage(id, p.getMessage());
}

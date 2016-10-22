#include "RedTubo.hpp"


RedTubo::RedTubo(std::initializer_list<std::shared_ptr<CPU>> il): Process("RedTubo"){
  for(auto cpu: il){
    cpu->setEnvioMensajeCallback([this](Id destino, MessagePE message){
        this->enviarMensaje(destino, message);
      });

    for(auto id: cpu->getIdsPEs()){
      this->cpus.insert({id, cpu});
    }
  }

  std::make_heap(this->current.begin(), this->current.end());
}

void RedTubo::enviarMensaje(Id destino, MessagePE message){

  // el mensaje es dividido en paquetes que son puestos en un buffer de entrada
  // de la red tubo a la espera de ser enviados por la red.

  auto ptr = message.getPointer();

  unsigned int number = 0;
  bool last = false;

  for(unsigned int restante = message.getSize();restante > 0;restante = restante - PACKET_SIZE, number++){
    auto pkt = Packet(ptr, number, last);
    this->input_buffer.push_back(std::make_tuple(destino, pkt));
  }

  std::get<1>(this->input_buffer.at(this->input_buffer.size() - 1)).setLast(true);

  this->activate();
}


void RedTubo::inner_body(){
  while(this->run){
    if(this->current.empty()){
      this->intentarAgregarPaquete();
      this->passivate();
    }else{
      //obtenemos el que tiene menor remaining time, este va a ser nuestro hold
      //y es el que está al principio del heap

      Packet p;

      std::tie(std::ignore, p) = this->current.at(0);
      double to_hold = p.getRemainingTime();

      //sabemos cuanto esperar, esperamos...
      hold(to_hold);

      //ahora, a todos los paquetes que están esperando, tenemos que restarle el
      //tiempo a esperar. Dado que a todos les restamos la misma cantidad, la
      //propiedad de heap debería mantenerse

      for(auto &t: this->current){
        Packet &p = std::get<1>(t);
        p.restarTiempo(to_hold);
      }
     
      // ahora debemos sacar los elementos del heap current. Si el elemento es
      // final (el ultimo packet) entonces le mandamos el mensaje a la CPU, si
      // no, solamente lo descartamos

      for(auto it = this->current.begin(); it != this->current.end();it++){
        Packet p;
        Id id;
        std::tie(id, p) = *it;

        if(p.getRemainingTime() <= 0){
            //hay que ver si era el final
            if(p.isLast()){
              //era el ultimo, entonces pasamos el mensaje a la CPU
              this->entregarMensaje(id, p);
            }
            //sacamos el elemento del heap
            this->current.erase(it);
            std::pop_heap(this->current.begin(), this->current.end());
            //ahora sacamos el mensaje de la tabla hash de manera de permitir
            //que entre otro posible paquete del mismo mensjae
            this->existe.erase(p.getMessage()->getId());
        }
      }
      this->intentarAgregarPaquete();
    }
  }
}



bool RedTubo::tuboLleno(){
  unsigned int total = 0;
  for(auto &t: this->current){
    Packet p;
    std::tie(std::ignore, p) = t;
    total = total + p.getPacketSize();
  }

  return total > ANCHO_BANDA_INSTANTE;
}

void RedTubo::intentarAgregarPaquete(){
  if(!this->input_buffer.empty()){
    if(!this->tuboLleno()){
      //intentamos poner un nuevo paquete que no sea parte de los mensajes que
      //ya están en la red

      for(auto t: this->input_buffer){
        Packet p;
        std::tie(std::ignore, p) = t;

        auto existe = this->existe.find(p.getMessage()->getId());
        if(existe == this->existe.end()){
          //el mensaje no se encuentra en la red, por lo tanto podemos enviarlo
          this->current.push_back(t);
          std::push_heap(this->current.begin(), this->current.end());
          this->existe.insert({p.getMessage()->getId(), true});
        }
      }
    }
  }
}



void RedTubo::entregarMensaje(Id id, Packet p){
  //tenemos que encontrar la CPU a la cual vamos a enviar el mensaje del
  //paquete. Para un mensaje, buscamos en cual de todas las CPUs se encuentra el
  //PE con el ID, si no lo encontramos, entonces en alguna parte estamos mal.

  auto cpu = this->cpus.find(id);
  assert(cpu != this->cpus.end());

  (*cpu).second->recibirMessage(id, *p.getMessage());
}

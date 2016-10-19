#include "CPU.hpp"


void CPU::inner_body(){
  while(this->run){
    if(this->planificacion.empty() && this->input_buffer.empty()){
      this->passivate();
    }

    if(!this->planificacion.empty()){
      //ejecutamos el PE
      PE_ptr pe;
      MessagePE message;
      std::tie(pe, message) = this->planificacion.front();

      hold(pe->getCostTime());

      this->planificacion.pop();
    }
    
    if(!this->input_buffer.empty()){
      //planificacion simple
      Id pe_id;
      MessagePE message;
      std::tie(pe_id, message) = this->input_buffer.front();

      auto found = std::find_if(this->pes.begin(), this->pes.end(), [pe_id](const PE_ptr &pe1){
            return pe_id == pe1->getId();
          });

      if(found == this->pes.end()){
        std::cerr << "El PE no se encuentra en la CPU de destino, ERROR DE PROGRAMACIÓN" << std::endl;
        exit(-1);
      }else{
        this->planificacion.push(std::make_tuple(*found, message));
        this->input_buffer.pop();
      }
    }

  }
}

CPU::CPU(std::initializer_list<PE*> il): Process("CPU"){
  for(PE *p: il){
    this->pes.push_back(std::shared_ptr<PE>(p));
  }
  this->numero_cores = 4;
  this->run = true;
}

void CPU::recibirMessage(Id destino, MessagePE message){
  this->activate();
  this->input_buffer.push(std::make_pair(destino, message));
}

void CPU::enviarMensaje(Id destino, MessagePE message){

}


void CPU::enviarMensaje3G(Id destino, MessageMD message){

}



void CPU::setEnvioMensajeCallback(std::function<void(Id, MessagePE)> fn){
  this->envio_mensaje_callback = fn;
}

bool CPU::contienePE(Id id){
  for(auto pe: this->pes){
    if(pe->getId() == id){
      return true;
    }
  }
  return false;
}

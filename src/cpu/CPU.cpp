#include "CPU.hpp"


void CPU::inner_body(){
  while(this->run){
    if(this->planificacion.empty() && this->input_buffer.empty()){
      this->passivate();
    }

    if(!this->planificacion.empty()){
      //ejecutamos el PE
      PE_ptr pe = std::get<0>(this->planificacion.front());
      MessagePE message = std::get<1>(this->planificacion.front());

      pe->setCurrentTime(time());
      double to_hold = pe->getCostTime();

      std::stringstream ss;
      ss << "Ejecutando el PE " << pe->getId();
      ss << " que es " << peNameToString(pe->getName());
      ss << " con el mensaje " << message.getId();
      ss << ", vamos a esperar " << to_hold;
      this->traza->puntoCPU(time(), ss);

      hold(to_hold);
      //Ahora enviamos el mensaje al siguiente PE

      std::vector<std::tuple<PEName, MessagePE>> nexts = pe->nextPE(message);

      for(auto t: nexts){
        PEName name = std::get<0>(t);
        MessagePE m = std::get<1>(t);

        std::stringstream ss;
        ss << "Enviando el mensaje " << m.getId();
        this->traza->puntoCPU(time(), ss);
        this->enviarMensaje(name, m);
      }

      this->planificacion.pop();
    }
    
    if(!this->input_buffer.empty()){
      //planificacion simple
      Id pe_id = std::get<0>(this->input_buffer.front());
      MessagePE message = std::get<1>(this->input_buffer.front());

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

CPU::CPU(std::initializer_list<std::shared_ptr<PE>> il): Process("CPU"){
  for(auto p: il){
    this->pes.push_back(p);
  }
  this->numero_cores = 4;
  this->run = true;
}

void CPU::recibirMessage(Id destino, MessagePE message){
  this->activate();
  this->input_buffer.push(std::make_pair(destino, message));
}

void CPU::enviarMensaje(PEName destino, MessagePE message){
  this->envio_mensaje_callback(destino, message);
}


void CPU::enviarMensaje3G(Id destino, MessageMD message){

}



void CPU::setEnvioMensajeCallback(std::function<void(PEName, MessagePE)> fn){
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


std::vector<Id> CPU::getIdsPEs(){
  std::vector<Id> ids;
  for(auto &pe: this->pes){
    ids.push_back(pe->getId());
  }

  return ids;
}



std::vector<std::tuple<PEName, Id>> CPU::getNamesPEs(){
  std::vector<std::tuple<PEName, Id>> names;
  for(auto pe: this->pes){
    names.push_back(std::make_tuple(pe->getName(), pe->getId()));
  }

  return names;
}

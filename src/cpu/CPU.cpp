#include "CPU.hpp"


void CPU::inner_body(){
  while(this->run){
    if(this->planificacion.empty() && this->input_buffer.empty()){
      this->passivate();
    }

    if(!this->planificacion.empty()){
      //ejemcutamos el PE
      auto pe = this->planificacion.front();

      //TODO: Ejecutar PE

      this->planificacion.pop();
    }
    
    if(!this->input_buffer.empty()){
      //TODO: Planfiicar el mensaje

    }

  }
}

CPU::CPU(std::initializer_list<PE*> il, IP _ip): NetworkComponent("CPU", _ip){
  for(PE *p: il){
    this->pes.push_back(std::shared_ptr<PE>(p));
  }
  this->numero_cores = 4;
}


#include "CPU.hpp"


void CPU::inner_body(){
  while(true){

  }
}

CPU::CPU(std::initializer_list<PE*> il): process("CPU"){
  for(PE *p: il){
    this->pes.push_back(std::shared_ptr<PE>(p));
  }
  this->numero_cores = 4;
}



void CPU::recibirMensaje(MessagePE m){
  auto encontrado = std::find_if(this->pes.begin(), this->pes.end(),
      [&](const std::shared_ptr<PE> &pe){
        return pe->getId() == m.getDestino();
      });

  // deberiamos siempre encontrar el PE si es que lo recibimos en esta CPU
  assert(encontrado != this->pes.end());

  // agregamos el PE a la plafinicación
  this->planificacion.push(*encontrado);
  this->activate();
}

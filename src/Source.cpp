#include "Source.hpp"


Source::Source(double et): process("source"){
  this->end_time = end_time;
}

Source::~Source(){
}

void Source::inner_body(){
  while(time() < this->end_time){
    this->porcentaje();
    // TODO: Hacer el envío de los mensajes a la red
    // Cuando se terminen de enviar mensajes, hacer break

  }


  while(time() < this->end_time){
    this->porcentaje();

  }
}


void Source::porcentaje(){
  int por = 100.0 / this->end_time * time();
  if(por % 10 == 0){
    std::cout << "Completado: " << por << "%" << std::endl;
  }
}

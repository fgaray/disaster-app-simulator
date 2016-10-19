#include "Source.hpp"


Source::Source(double et, std::shared_ptr<RedTubo> red): process("source"){
  this->end_time = end_time;
  this->red_tubo = red;
}

Source::~Source(){
}

void Source::inner_body(){
  while(time() < this->end_time){
    this->porcentaje();
    // TODO: Hacer el envío de los mensajes a la red
    // Cuando se terminen de enviar mensajes, hacer break
    
    //this->red_tubo->enviarMensaje(destino, mensaje);

  }


  // Esperamos a que termine la simulación, vamos mostrando el porcentaje de
  // ejecución completo
  while(time() < this->end_time){
    this->porcentaje();
  }

  //Hay que notificar a los demás objetos de la simulación que terminen de procesar


  for(auto callback: this->end_callbacks){
    callback();
  }
}


void Source::porcentaje(){
  int por = 100.0 / this->end_time * time();
  if(por % 10 == 0){
    std::cout << "Completado: " << por << "%" << std::endl;
  }
}



void Source::addEndCallback(std::function<void()> callback){
  this->end_callbacks.push_back(callback);
}

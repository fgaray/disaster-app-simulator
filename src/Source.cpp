#include "Source.hpp"


Source::Source(double et, handle<RedTubo> red, std::shared_ptr<Traza> traza): process("source"){
  this->end_time = et;
  this->red_tubo = red;
  this->traza = traza;
}

Source::~Source(){
}

void Source::inner_body(){
  auto distribucion = std::shared_ptr<Distribution>(new Distribution(AMOUNT_OF_TWEETS, TWEET_PER_SECOND));

  std::stringstream ss;
  ss << "Iniciando simulación, tiempo final: ";
  ss << this->end_time;
  unsigned int cantidad_menajes = 0; 
  while(time() < this->end_time && cantidad_menajes < AMOUNT_OF_TWEETS){
    this->porcentaje();
        auto tiempo_arribo = distribucion->GeneradorExp();
        //this->porcentaje();
        // TODO: Hacer el envío de los mensajes a la red
        // Cuando se terminen de enviar mensajes, hacer break

        auto destino = PEName::PEAdapter;
        auto mensaje = MessagePE(DEFAULT_MESSAGE_SIZE);
        this->traza->puntoSource(time(), "Generando un nuevo mensaje "+to_string(cantidad_menajes));

        this->red_tubo->enviarMensaje(destino, mensaje);
        //enviamos un mensaje cada 0.5 segundos
        hold(tiempo_arribo);
        //hold(10);
        cantidad_menajes++;
  }
  this->traza->puntoSource(time(), "No hay más mensajes a generar");

  // Esperamos a que termine la simulación, vamos mostrando el porcentaje de
  // ejecución completo
  while(time() < this->end_time){
    this->porcentaje();
    hold(1000);
  }

  //Hay que notificar a los demás objetos de la simulación que terminen de procesar

  this->traza->puntoSource(time(), "Terminando simulación");
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



void Source::addEndCallback(Process &p){
  this->end_callbacks.push_back(p.getEndCallback());
}

void Source::addEndCallback(handle<Process> p){
  this->end_callbacks.push_back(p->getEndCallback());
}

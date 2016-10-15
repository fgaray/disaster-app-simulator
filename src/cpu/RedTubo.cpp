#include "RedTubo.hpp"


RedTubo::RedTubo(std::initializer_list<CPU*> il): process("RedTubo"){
  for(CPU *cpu: il){
    this->cpus.push_back(std::shared_ptr<CPU>(cpu));
  }
  this->run = true;
}

void RedTubo::enviarMensaje(Id destino, MessagePE message){
  throw UNDEFINED;
}


void RedTubo::inner_body(){
  while(this->run){
    //TODO: hay que ver por cada mensaje que llega la latencia que asignamos.
    //Lo que tenemos que hacer es hacer un hold de la unidad mínimia de los
    //mensajes que estan guardados, y restamos ese tiempo al resto de los
    //mensajes guardados, hay que tener cuidado con los mensajes que entran ya
    //que pueden ser de un tiempo menor al que se está haciendo en el hold
    throw UNDEFINED;
  }
}

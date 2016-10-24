#include "MessagePE.hpp"

MessagePE::MessagePE(Id destino, unsigned int size){
  this->d = destino;
  this->size = size;
  this->id_message = unique_id();
}

MessagePE::MessagePE(unsigned int size){
  this->size = size;
  this->id_message = unique_id();
}

MessagePE::MessagePE(){
  this->id_message = unique_id();
}

Id MessagePE::getDestino(){
  return this->d;
}


unsigned int MessagePE::getSize(){
  return this->size;
}



Id MessagePE::getId(){
  return this->id_message;
}


void MessagePE::setDestino(Id id){
  this->d = id;
}

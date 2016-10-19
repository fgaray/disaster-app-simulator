#include "MessagePE.hpp"

MessagePE::MessagePE(Id destino, unsigned int s){
  this->d = destino;
  this->size = d;
}

MessagePE::MessagePE(){
}

Id MessagePE::getDestino(){
  return this->d;
}


unsigned int MessagePE::getSize(){
  return this->size;
}

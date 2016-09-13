#include "MessagePE.hpp"

MessagePE::MessagePE(size_t destino){
  this->d = destino;
}

size_t MessagePE::getDestino(){
  return this->d;
}


#include "MessagePE.hpp"

MessagePE::MessagePE(Id destino){
  this->d = destino;
}

Id MessagePE::getDestino(){
  return this->d;
}


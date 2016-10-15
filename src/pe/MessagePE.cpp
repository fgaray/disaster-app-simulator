#include "MessagePE.hpp"

MessagePE::MessagePE(Id destino){
  this->d = destino;
}

MessagePE::MessagePE(){
}

Id MessagePE::getDestino(){
  return this->d;
}


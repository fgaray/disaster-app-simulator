#include "MessageMD.hpp"

MessageMD::MessageMD(Id destino){
  this->d = destino;
}


Id MessageMD::getDestino(){
  return this->d;
}


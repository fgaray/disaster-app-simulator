#include "MessageMD.hpp"

MessageMD::MessageMD(Id destino){
  this->d = destino;
}


MessageMD::MessageMD(){
}

Id MessageMD::getDestino(){
  return this->d;
}


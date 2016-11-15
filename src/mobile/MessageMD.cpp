#include "MessageMD.hpp"

MessageMD::MessageMD(Id destino, unsigned int size){
  this->d = destino;
  this->size = size;
  this->tageado = false;
}

MessageMD::MessageMD(){

}

unsigned int MessageMD::getSize(){
	return this->size;
}

Id MessageMD::getDestino(){
  return this->d;
}

Id MessageMD::getId(){
  return this->id_message;
}

void MessageMD::setTag(){
	this->tageado = true;
}


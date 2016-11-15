#include "MessageMD.hpp"

static Id current_id = 0;

MessageMD::MessageMD(Id destino, unsigned int size){
  this->d = destino;
  this->size = size;
  this->id_message = current_id;
  current_id++;
  this->tageado = false;
}

MessageMD::MessageMD(){
	this->id_message = current_id;
	current_id++;
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


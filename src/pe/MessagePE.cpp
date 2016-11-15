#include "MessagePE.hpp"

static Id current_id = 0;


MessagePE::MessagePE(Id destino, unsigned int size){
  this->d = destino;
  this->size = size;
  this->id_message = current_id;
  current_id++;
  this->size_seteado = true;
  this->dispositivo_movil_seted = false;
  this->tag = false;
}

MessagePE::MessagePE(unsigned int size){
  this->size = size;
  this->id_message = current_id;
  current_id++;
  this->size_seteado = true;
  this->dispositivo_movil = -1;
  this->dispositivo_movil_seted = false;
  this->tag = false;
}

MessagePE::MessagePE(){
  this->id_message = current_id;
  current_id++;
  this->size_seteado = false;
  this->tag = false;
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



void MessagePE::setTweetId(Id tweet){
  this->tweet = tweet;
}

Id MessagePE::getTweetId(){
  return this->tweet;
}



Id MessagePE::getDispositivoMovil(){
  assert(this->dispositivo_movil_seted != false);
  return this->dispositivo_movil;
}

void MessagePE::setDispositivoMovil(Id dispositivo_movil){
  this->dispositivo_movil = dispositivo_movil;
  this->dispositivo_movil_seted = true;
}

void MessagePE::setTag(){
  this->tag = true;
}

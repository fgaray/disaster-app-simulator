#include "MessagePE.hpp"

static Id current_id = 0;


MessagePE::MessagePE(Id destino, unsigned int size){
  this->d = destino;
  this->size = size;
  this->id_message = current_id;
  current_id++;
  this->size_seteado = true;
}

MessagePE::MessagePE(unsigned int size){
  this->size = size;
  this->id_message = current_id;
  current_id++;
  this->size_seteado = true;
}

MessagePE::MessagePE(){
  this->id_message = current_id;
  current_id++;
  this->size_seteado = false;
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

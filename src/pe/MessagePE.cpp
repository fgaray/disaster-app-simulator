#include "MessagePE.hpp"

MessagePE::MessagePE(Id destino, unsigned int size){
  this->d = destino;
  this->size = size;
}

MessagePE::MessagePE(){
}

Id MessagePE::getDestino(){
  return this->d;
}


unsigned int MessagePE::getSize(){
  return this->size;
}

std::shared_ptr<MessagePE> MessagePE::getPointer(){
  auto m = new MessagePE(this->d, this->size);
  return std::shared_ptr<MessagePE>(m);
}



MessagePE MessagePE::getScalar(){
  return MessagePE(this->d, this->size);
}

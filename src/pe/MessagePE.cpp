#include "MessagePE.hpp"

MessagePE::MessagePE(Id id_message, Id destino, unsigned int size){
  this->d = destino;
  this->size = size;
  this->id_message = id_message;
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
  auto m = new MessagePE(this->id_message, this->d, this->size);
  return std::shared_ptr<MessagePE>(m);
}



MessagePE MessagePE::getScalar(){
  return MessagePE(this->id_message, this->d, this->size);
}


Id MessagePE::getId(){
  return this->id_message;
}

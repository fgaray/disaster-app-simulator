#include "NetworkComponent.hpp"

NetworkComponent::NetworkComponent(std::string name, IP _ip): process(name){
  this->ip = _ip;
  this->run = true;
}

IP NetworkComponent::getIP(){
  return this->ip;
}


void NetworkComponent::inner_body(){
  while(this->run){
    if(this->input_buffer.empty()){
      this->passivate();
    }

    auto e = this->input_buffer.front();
    this->component_inner_body(e);
    this->input_buffer.pop();
  }
}


void NetworkComponent::end_run(){
  this->run = false;
}


void NetworkComponent::receiveMessage(MessagePE pe, IP destino){
  if(destino == this->ip){
    this->input_buffer.push(make_tuple<>(pe, destino));
    this->activate();
  }else{
    //TODO: Enviar el mensaje hacia el siguiente componente
    throw UNDEFINED;
  }
}


void NetworkComponent::enviarMensaje(MessagePE pe, IP destino){
  throw UNDEFINED;
}

#include "Network3G.hpp"


Network3G::Network3G(): Process("Network"){

}

void Network3G::enviarMensajeHaciaMD(Id hacia, MessageMD m){
  throw UNDEFINED;
}

void Network3G::enviarMensajeHaciaCluster(MessageMD m){
  throw UNDEFINED;
}


std::function<void(MessageMD)> Network3G::getSendCallback(){
  return [this](MessageMD message){
    this->enviarMensajeHaciaCluster(message);
  };
}

std::function<void(std::shared_ptr<Device>)> Network3G::getMoveCallback(){
  throw UNDEFINED;
}

void Network3G::inner_body(){
  throw UNDEFINED;
}


std::function<void(Device*)> Network3G::getCallbackNotificarMovimiento(){
  return [this](Device *d){
    this->notificarMovimientoDevice(d);
  };
}


void Network3G::notificarMovimientoDevice(Device *d){
  throw UNDEFINED;
}


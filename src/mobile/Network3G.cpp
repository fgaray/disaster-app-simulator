#include "Network3G.hpp"


Network3G::Network3G(): process("Network"){

}

void Network3G::enviarMensajeHaciaMD(Id hacia, MessageMD m){
  throw UNDEFINED;
}

void Network3G::enviarMensajeHaciaCluster(Id desde, MessageMD m){
  throw UNDEFINED;
}


std::function<void(Id, MessageMD)> Network3G::getSendCallback(){
  throw UNDEFINED;
}

std::function<void(std::shared_ptr<Device>)> Network3G::getMoveCallback(){
  throw UNDEFINED;
}

void Network3G::inner_body(){
  throw UNDEFINED;
}

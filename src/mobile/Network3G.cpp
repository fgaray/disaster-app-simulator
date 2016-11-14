#include "Network3G.hpp"

#include <algorithm>



Network3G::Network3G(std::initializer_list<handle<Device>> dv, std::initializer_list<handle<Antena>> al): Process("Network"){
  for (auto ant : al){
    this->antenas.insert({ant->getId(), ant});
  }

  for (auto device : dv){
    //Para cada device, encontrar antena
    std::vector<std::tuple<handle<Antena>, double>> dist_vect;
    for (auto ant = this->antenas.begin(); ant != this->antenas.end(); ++ant ){
      double dev_dist = ant->second->distancia(device);

      if((*ant).second->getRadio() > dev_dist){
        dist_vect.push_back(std::make_tuple((*ant).second, dev_dist));
      }
    }
    std::sort(dist_vect.begin(), dist_vect.end(), [](auto &left, auto &right) {
        return std::get<1>(left) < std::get<1>(right);
        });

    this->devices_antenas.insert({device->getId(), std::get<0>(dist_vect.at(0))});
  }

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


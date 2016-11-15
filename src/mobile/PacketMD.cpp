#include "PacketMD.hpp"

PacketMD::PacketMD(MessageMD message, unsigned int number, bool last){
  this->message = message;
  this->number = number;
  this->last = last;

  // El tiempo restante es el tamaño del paquete en bits divivido por la
  // velocidad en bps de la red tubo. Dado que 1s = 1000, entonces SIZE /
  // VELOCIAD retorna los segundos, al multiplicarlo por 1000 nos da el tiempo
  // en nuestra escala.
  this->remaining_time = double(PACKET_SIZE) / double(VELOCIDAD_RED_3G) * 1000.0;
}

unsigned int PacketMD::getMessageSize(){
  return this->message.getSize();
}

unsigned int PacketMD::getPacketSize(){
  return this->size;
}

MessageMD PacketMD::getMessage(){
  return this->message;
}

bool PacketMD::isLast(){
  return this->last;
}

void PacketMD::setLast(bool last){
  this->last = last;
}


void PacketMD::restarTiempo(double t){
  this->remaining_time = this->remaining_time - t;
  if(this->remaining_time < 0){
    this->remaining_time = 0;
  }
}


double PacketMD::getRemainingTime(){
  return this->remaining_time;
}


bool PacketMD::operator<(const PacketMD& p) const{
  //esta comparación es al revez, de manera tal que en el heap quede el menor al
  //principio dado que C++ pone el mayor al principio.
  return this->remaining_time > p.remaining_time;
}



unsigned int PacketMD::getNumber(){
  return this->number;
}

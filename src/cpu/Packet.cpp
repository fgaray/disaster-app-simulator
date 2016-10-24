#include "Packet.hpp"

Packet::Packet(MessagePE message, unsigned int number, bool last){
  this->message = message;
  this->number = number;
  this->last = last;

  // El tiempo restante es el tamaño del paquete en bits divivido por la
  // velocidad en bps de la red tubo. Dado que 1s = 1000, entonces SIZE /
  // VELOCIAD retorna los segundos, al multiplicarlo por 1000 nos da el tiempo
  // en nuestra escala.
  this->remaining_time = double(PACKET_SIZE) / double(VELOCIDAD_RED_TUBO) * 1000.0;
}

unsigned int Packet::getMessageSize(){
  return this->message.getSize();
}

unsigned int Packet::getPacketSize(){
  return this->size;
}

MessagePE Packet::getMessage(){
  return this->message;
}

bool Packet::isLast(){
  return this->last;
}

void Packet::setLast(bool last){
  this->last = last;
}


void Packet::restarTiempo(double t){
  this->remaining_time = this->remaining_time - t;
  if(this->remaining_time < 0){
    this->remaining_time = 0;
  }
}


double Packet::getRemainingTime(){
  return this->remaining_time;
}


bool Packet::operator<(const Packet& p) const{
  //esta comparación es al revez, de manera tal que en el heap quede el menor al
  //principio dado que C++ pone el mayor al principio.
  return this->remaining_time > p.remaining_time;
}



unsigned int Packet::getNumber(){
  return this->number;
}

#include "Antena.hpp"


Antena::Antena(double _x, double _y, double _radio){
  this->x = _x;
  this->y = _y;
  this->radio = _radio;
}

double Antena::distancia(std::shared_ptr<Device> device) const{
  throw UNDEFINED;
}


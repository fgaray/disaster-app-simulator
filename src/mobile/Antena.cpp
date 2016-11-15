#include "Antena.hpp"


Antena::Antena(double _x, double _y, double _radio): Process("Antena"){
  this->x = _x;
  this->y = _y;
  this->radio = _radio;
}

double Antena::distancia(handle<Device> device) const{
	double dist_x = this->x - device->getX();
	double dist_y = this->y - device->getY();
	return sqrt(pow(dist_x,2) + pow(dist_y,2));
}

Id Antena::getId(){
  return this->id;
}



double Antena::getRadio(){
  return radio;
}


void Antena::inner_body(){

}

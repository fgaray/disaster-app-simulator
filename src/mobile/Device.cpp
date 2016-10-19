#include "Device.hpp"


Device::Device(std::function<void(std::shared_ptr<Device>)> _move_device, send_callback _send_message): Process("Device"){
  this->move_device = _move_device;
  this->send_message = _send_message;
  this->x = 0;
  this->y = 0;
}


Id Device::getId() const{
  throw UNDEFINED;
}

void Device::inner_body(){
  throw UNDEFINED;
}

void Device::agregarPosicion(double time, double _x, double _y){
  this->posiciones.push(std::make_tuple<>(time, _x, _y));
}


double Device::getX() const{
  return this->x;
}

double Device::getY() const{
  return this->y;
}

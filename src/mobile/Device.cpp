#include "Device.hpp"


Device::Device(std::function<void(std::shared_ptr<Device>)> _move_device, send_callback _send_message, std::queue<position> posiciones): Process("Device"){
  this->move_device = _move_device;
  this->send_message = _send_message;
  this->x = 0;
  this->y = 0;
  this->posiciones = posiciones;


  this->movimiento = handle<Movimiento>(
      new Movimiento(
        [this](double x, double y){
          this->x = x;
          this->y = y;
          position next = this->posiciones.front();
          if(this->posiciones.size() > 1){
            // En caso de tener más de una siguiente posicion, sacamos el que
            // está en la cima de la cola para representar el movimiento
            this->posiciones.pop();
          }
          return next;
        }));
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


void Device::endSimulation(){
  this->movimiento->endSimulation();
  Process::endSimulation();
}

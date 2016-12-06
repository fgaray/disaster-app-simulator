#include "Movimiento.hpp"


Movimiento::Movimiento(std::function<position(double, double)> ready_callback): Process("Movimiento"){
  this->ready_callback = ready_callback;
}


void Movimiento::inner_body(){
  while(this->run){
    double to_hold, x, y;
    std::tie(to_hold, x, y) = next;
    hold(to_hold);
    this->next = this->ready_callback(x, y);
  }
}


void Movimiento::setNext(position next){
  this->next = next;
  this->activate();
}

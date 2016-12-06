#include "Core.hpp"

#include "../common/Distribution.hpp"

Core::Core(): Process("Core"){
  this->isEmpty = true;
  this->current_pe = nullptr;
  this->tiempo_iddle = 0;
  this->tiempo_uso = 0;
  this->tiempo_parada = 0;
}




void Core::inner_body(){
  while(this->run){
    assert(this->current_pe != nullptr);

    this->traza->puntoCore(time(), ">>>Ejecutando PE en core");
    double to_hold = this->current_pe->getCostTime();
    hold(to_hold);
    this->tiempo_uso += to_hold;

    //notificamos a la CPU que estamos ready
    this->cpu_callback(this->current_pe->nextPE(this->message));

    this->current_pe = nullptr;
    this->isEmpty = true;
    this->tiempo_iddle += time() - this->tiempo_parada;
    this->tiempo_parada = time();
    passivate();
  }


}

void Core::set_cpu_callback(std::function<void(std::vector<std::tuple<PEName, MessagePE>>)> fn){
    this->cpu_callback = fn;
}

bool Core::empty() const{
  return this->isEmpty;
}

bool Core::ejecutando(PE_ptr pe) const{
  return !this->isEmpty && this->current_pe == pe;
}

void Core::ejecutar(PE_ptr pe, MessagePE message){
  this->current_pe = pe;
  this->message = message;
  this->isEmpty = false;
  this->traza->puntoCore(time(), "Vamos a ejecutar el PE");
  this->activate();
}

double Core::utilizacion(){
  double total = this->tiempo_iddle + this->tiempo_uso;
  return 100.0 * this->tiempo_uso / total;
}

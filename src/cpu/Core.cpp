#include "Core.hpp"


Core::Core(): Process("Core"){
  this->isEmpty = true;
  this->current_pe = nullptr;
}




void Core::inner_body(){
  while(this->run){
    assert(this->current_pe != nullptr);

    this->traza->puntoCore(time(), ">>>Ejecutando PE en core");
    hold(this->current_pe->getCostTime());

    //notificamos a la CPU que estamos ready
    this->cpu_callback(this->current_pe->nextPE(this->message));

    this->current_pe = nullptr;
    this->isEmpty = true;
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

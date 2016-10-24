#include "Process.hpp"

Process::Process(const std::string &name): process(name){
  this->run = true;
  this->name = name;
}

void Process::endSimulation(){
  this->run = false;
  this->traza->puntoFin(time(), "Terminando de ejecutar " + this->name);
}

void Process::setTraza(std::shared_ptr<Traza> traza){
  this->traza = traza;
}
function<void()> Process::getEndCallback(){
  return [this](){
    this->endSimulation();
  };
}

#include "Process.hpp"

Process::Process(const std::string &name): process(name){
  this->run = true;
}



void Process::endSimulation(){
  this->run = false;
  this->activate();
}

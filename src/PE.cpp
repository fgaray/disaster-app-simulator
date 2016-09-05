#include "PE.hpp"

static size_t id_counter = 0;

PE::PE(const std::string &nombre_pe){
  this->id = id_counter;
  id_counter++;
  this->nombre = nombre_pe;
}

size_t PE::getId(){
  return this->id;
}

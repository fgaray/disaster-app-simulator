#include "Undefined.hpp"

const char* Undefined::what(){
  std::string str = " no está definida";
  return (this->nombre + str).c_str();
}

Undefined::Undefined(const char *nombre_fn){
  this->nombre = nombre_fn;
}

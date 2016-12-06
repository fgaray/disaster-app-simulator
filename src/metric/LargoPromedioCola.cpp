#include "LargoPromedioCola.hpp"


static LargoPromedioCola largo;

LargoPromedioCola::LargoPromedioCola(){

}

void LargoPromedioCola::agregarTamano(size_t n){
  this->valores.push_back(n);
}

double LargoPromedioCola::obtenerPromedio(){
  size_t suma = 0;

  for(size_t n: this->valores){
    suma += n;
  }

  return (double)suma / (double)this->valores.size();

}


void agregarTamano(size_t n){
  largo.agregarTamano(n);
}



double obtenerPromedio(){
  return largo.obtenerPromedio();
}

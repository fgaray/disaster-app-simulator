#include "BalanceCarga.hpp"

static BalanceCarga balance;

void agregarBalance(string nombre, size_t n){
  balance.agregarBalance(nombre, n);
}



void imprimirValoresBalance(){
  return balance.imprimirValoresBalance();
}



void BalanceCarga::agregarBalance(string nombre_pe, size_t n){
  auto cola = colas.find(nombre_pe);
  if(cola == colas.end()){
    colas.insert({nombre_pe, make_tuple(1, n)});
  }else{
   size_t cantidad, suma;
   tie(cantidad, suma) = (*cola).second;
   colas.insert({nombre_pe, make_tuple(cantidad + 1, suma + n)});
  }
}

void BalanceCarga::imprimirValoresBalance(){
  for(auto cola: this->colas){
    auto tupla = cola.second;
    size_t cantidad, suma;
    tie(cantidad, suma) = tupla;
    cout << cola.first << ":" << (double)suma/(double)cantidad << endl;
  }
}

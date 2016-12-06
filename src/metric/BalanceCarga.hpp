#ifndef _H_BALANCE_CARGA_H_
#define _H_BALANCE_CARGA_H_

#include <unordered_map>
#include <string>
#include <iostream>
#include <tuple>
using namespace std;


void agregarBalance(string nombre_pe, size_t n);
void imprimirValoresBalance();

class BalanceCarga{

  private:
    // (cantidad, suma)
    unordered_map<string, tuple<size_t, size_t>> colas;

  public:

    void agregarBalance(string nombre_pe, size_t n);
    void imprimirValoresBalance();

};



#endif

#ifndef _H_ROUND_ROBIN_ITERATOR_H_
#define _H_ROUND_ROBIN_ITERATOR_H_

#include <vector>
#include <iostream>
#include <cassert>
#include "UniqueIdGenerator.hpp"

/**
 * Dado que necesitamos hacer round robin sobre una lista de PEs, es necesario
 * tener un iterator que permita hacer ciclos. Esta clase implementa justamente
 * eso.
 *
 * A partir de un iterator begin y end, va guardando el estado actual y utiliza
 * begin y end para realizar los ciclos.
 *
 * Funciona solamente para vectores, no necesitamos otros contenedores
 *
 * Obviamente el vector desde el cual se obtienen los iterators begin y end no
 * deben cambiar. Si cambian entonces este iterator se vuelve inválido.
 *
 * */
class RoundRobinIterator{
  private:
    size_t current;
    size_t max;

  public:
    RoundRobinIterator(size_t max);
    size_t getNext();

};

#endif

#ifndef _H_PE_
#define _H_PE_

#include <cstdio>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include "../common/UniqueIdGenerator.hpp"
#include "MessagePE.hpp"
#include <memory>

#include "PEName.hpp"



/**
 * La instanciación de esta clase NO es thread safe.
 * */

class PE{
  protected:
    Id id;
    double currentTime;
  public:
    PE(){
      //cremos un ID de acuerdo a UniqueIdGenerator
      this->id = unique_id();
    }

    Id getId(){
      return this->id;
    }

    /**
     * Entrega el Id del siguiente PE a ser ejecutado. Se puede buscar el Id en
     * la tabla de routeo.
     *
     * @param message El mensaje que se recibe para decidir hacia donde enviar
     * el siguiente
     *
     * @return El Id el siguiente PE
     *
     * */
    virtual std::vector<std::tuple<PEName, MessagePE>> nextPE(MessagePE message) = 0;

    /**
     * Retorna el nombre del PE
     * */
    virtual PEName getName() = 0;

    void setCurrentTime(double currentTime){
        this->currentTime = currentTime;
    }

    /**
     * Retorna el costo de ejecutar este PE.
     * Cada 1000 es 1 segundo
     * */
    virtual double getCostTime() = 0;

};

typedef std::shared_ptr<PE> PE_ptr;

#endif

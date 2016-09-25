#ifndef _H_PE_
#define _H_PE_

#include <cstdio>
#include <string>
#include "../common/UniqueIdGenerator.hpp"
#include "MessagePE.hpp"


/**
 * La instanciación de esta clase NO es thread safe.
 * */

class PE{
  private:
    Id id;
    std::string nombre;
  public:
    PE(const std::string &nombre_pe){
      this->nombre = nombre_pe;
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
    virtual Id nextPE(const MessagePE &message) = 0;

    /**
     * Transforma el mensaje. Por defecto la transformación es la identidad.
     * */
    MessagePE transform(const MessagePE &message){
      return message;
    }

    /**
     * Retorna el costo de ejecutar este PE
     * */
    virtual double getCostTime() = 0;

};

#endif

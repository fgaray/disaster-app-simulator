#ifndef _H_MESSAGE_
#define _H_MESSAGE_

#include <cstdlib>
#include <memory>
#include <memory>
#include "PEName.hpp"

#include "../common/UniqueIdGenerator.hpp"


enum class TipoMensajePE{
  PyBossa,
  Clasificador
};


/**
 * Un mensaje genérico, puede ser de dos tipos: Uno para pybossa y otro para el
 * clasificadr (TODO: Cambiar si es necesario)
 *
 * */
class MessagePE{
  private:
    Id d;
    Id id_message;
    unsigned int size;
  public:
    MessagePE(Id destino, unsigned int size);
    MessagePE(unsigned int size);
    MessagePE();
    Id getDestino();
    unsigned int getSize();
    Id getId();
    void setDestino(Id id);
};

#endif

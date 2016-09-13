#ifndef _H_MESSAGE_
#define _H_MESSAGE_

#include <cstdlib>

/**
 * Un mensaje genérico
 *
 * */
class MessagePE{
  private:
    size_t d;
  public:
    MessagePE(size_t destino);
    size_t getDestino();
};

#endif

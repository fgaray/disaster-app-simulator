#ifndef _H_MESSAGE_MD_
#define _H_MESSAGE_MD_

#include <cstdlib>

#include "../common/UniqueIdGenerator.hpp"


class MessageMD{
  private:
    Id d;
    Id id_message;
    unsigned int size;
    bool tageado;
  public:
    MessageMD(Id destino, unsigned int size);
    MessageMD();
    Id getDestino();
    Id getId();
    unsigned int getSize();
    void setTag();
};

#endif

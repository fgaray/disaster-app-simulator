#ifndef _H_MESSAGE_
#define _H_MESSAGE_

#include <cstdlib>

#include "../common/UniqueIdGenerator.hpp"


class MessageMD{
  private:
    Id d;
  public:
    MessageMD(Id destino);
    Id getDestino();
};

#endif

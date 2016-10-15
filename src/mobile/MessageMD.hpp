#ifndef _H_MESSAGE_MD_
#define _H_MESSAGE_MD_

#include <cstdlib>

#include "../common/UniqueIdGenerator.hpp"


class MessageMD{
  private:
    Id d;
  public:
    MessageMD();
    MessageMD(Id destino);
    Id getDestino();
};

#endif

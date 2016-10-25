#ifndef _H_MESSAGEBROKER_
#define _H_MESSAGEBROKER_

#include <cstdlib>
#include <memory>
#include <memory>
#include <cassert>
#include "PEName.hpp"
#include "MessagePE.hpp"

#include "../common/UniqueIdGenerator.hpp"


/**
 * Un mensaje genérico, puede ser de dos tipos: Uno para pybossa y otro para el
 * clasificadr (TODO: Cambiar si es necesario)
 *
 * */
class MessageBroker: public MessagePE{
  private:
    Id id;
  public:
    MessageBroker(unsigned int size, Id id);
    Id getIdTweet();
};

#endif

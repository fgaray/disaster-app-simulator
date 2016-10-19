#ifndef _H_RED_TUBO_
#define _H_RED_TUBO_

#include <vector>

#include "CPU.hpp"
#include "../pe/PE.hpp"
#include "../common/Undefined.hpp"
#include "../common/Process.hpp"
#include "../common/Config.hpp"


typedef std::queue<std::tuple<Id, MessagePE>> buffer;

/**
 * La red tubo funciona como si fuera un solo switch que comunica todo
 *
 * */
class RedTubo: Process{
  private:
    vector<CPU_ptr> cpus;
    buffer input_buffer;

  public:
    RedTubo(std::initializer_list<std::shared_ptr<CPU>> il);
    void enviarMensaje(Id destino, MessagePE message);
    void inner_body();

};

#endif

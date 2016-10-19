#ifndef _H_RED_TUBO_
#define _H_RED_TUBO_

#include <vector>

#include "CPU.hpp"
#include "../pe/PE.hpp"
#include "../common/Undefined.hpp"
#include "../common/Process.hpp"

class RedTubo: Process{
  private:
    vector<CPU_ptr> cpus;
    bool run;

  public:
    RedTubo(std::initializer_list<CPU*> il);
    void enviarMensaje(Id destino, MessagePE message);
    void inner_body();

};

#endif

#ifndef _H_RED_TUBO_
#define _H_RED_TUBO_

#include <process.hh>
#include <vector>

#include "CPU.hpp"
#include "../pe/PE.hpp"
#include "../common/Undefined.hpp"

class RedTubo: process{
  private:
    vector<CPU_ptr> cpus;
    bool run;

  public:
    RedTubo(std::initializer_list<CPU*> il);
    void enviarMensaje(Id destino, MessagePE message);
    void inner_body();

};

#endif

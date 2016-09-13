#ifndef _H_CPU_
#define _H_CPU_

#include <initializer_list>
#include <vector>
#include <memory>
#include <algorithm>
#include <queue>

#include <process.hh>

#include "../pe/MessagePE.hpp"
#include "../pe/PE.hpp"


/**
 * Un CPU tiene varios Cores para el cual se debe hacer planificación de los PE
 * que quieran ejecutarse.
 *
 * Construir utilizando CPU{PE1, PE2, PE3...} (con llaves y no parentesis)
 *
 * Esta CPU simula comunicación en el mismo sistema por medio de niveles de
 * cache/ram y si es necesario envía el mensaje por la red a otras CPUs. Además
 * dentro de este mismo sistema realiza la planificación de los PEs de acuerdo a
 * roudrobin.
 *
 * Cada vez que un mensaje llega si ve para cual de todos los PEs es. Se
 * selecciona ese PE y se agrega a la cola de planificación. Desde esa cola 
 *
 * */
class CPU: public process{
  protected:
    //Los PEs asignados a esta CPU. Ellos comparten el número de cores que
    //existen.
    size_t numero_cores;
    std::vector<std::shared_ptr<PE>> pes;
    void inner_body();
    std::queue<std::shared_ptr<PE>> planificacion;

  public:
    CPU(std::initializer_list<PE*> il);
    void recibirMensaje(MessagePE m);
};

#endif

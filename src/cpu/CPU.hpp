#ifndef _H_CPU_
#define _H_CPU_

#include <initializer_list>
#include <vector>
#include <memory>
#include <algorithm>
#include <queue>

#include <process.hh>

#include "../pe/MessagePE.hpp"
#include "../mobile/MessageMD.hpp"
#include "../pe/PE.hpp"
#include "../common/IP.hpp"

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
    std::vector<PE_ptr> pes;
    std::queue<std::tuple<Id, MessagePE>> input_buffer;
    std::queue<std::tuple<PE_ptr, MessagePE>> planificacion;
    bool run;
    void enviarMensaje(Id destino, MessagePE message);
    void enviarMensaje3G(Id destino, MessageMD message);

  public:
    CPU(std::initializer_list<PE*> il);
    void inner_body();
    void recibirMessage(Id destino, MessagePE message);
};

#endif

#ifndef _H_CPU_
#define _H_CPU_

#include <initializer_list>
#include <vector>
#include <memory>
#include <algorithm>
#include <queue>
#include <iostream>
#include <unordered_map>


#include "../pe/MessagePE.hpp"
#include "../mobile/MessageMD.hpp"
#include "../pe/PE.hpp"
#include "../common/Process.hpp"


class Planificacion{
  private:
    bool contiene;
    PE_ptr pe;
    MessagePE message;
    double tiempo_restante;

  public:
    Planificacion(std::tuple<PE_ptr, MessagePE> planificacion);
    Planificacion();
    std::tuple<PE_ptr, MessagePE> get();
    void set(std::tuple<PE_ptr, MessagePE> planificacion);
    void ejecutar(double t);
    bool contienePlanificacion();
    MessagePE getMessage();
    double restante() const;
    void remove();
    PE_ptr getPE();
};



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
class CPU: public Process{
  protected:
    //Los PEs asignados a esta CPU. Ellos comparten el número de cores que
    //existen.
    size_t numero_cores;
    std::vector<PE_ptr> pes;
    std::vector<std::tuple<Id, MessagePE>> input_buffer;
    void enviarMensaje(PEName destino, MessagePE message);
    void enviarMensaje3G(Id destino, MessageMD message);
    std::function<void(PEName, MessagePE)> envio_mensaje_callback;
    std::vector<Planificacion> cores;
    std::unordered_map<Id, bool> ejecutando;
    
    void intentar_agregar();

  public:
    CPU(std::initializer_list<std::shared_ptr<PE>> il);
    void inner_body();
    void recibirMessage(Id destino, MessagePE message);

    /**
     * Si la CPU quiere enviar un archivo, entonces tiene que mandar el mensaje
     * mediante el callaback que le pasó la red tubo
     * */
    void setEnvioMensajeCallback(std::function<void(PEName, MessagePE)> fn);
    bool contienePE(Id id);
    std::vector<Id> getIdsPEs();
    std::vector<std::tuple<PEName, Id>> getNamesPEs();
    bool existePlanificacion();
};

typedef handle<CPU> CPU_ptr;

#endif

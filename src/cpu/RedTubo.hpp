#ifndef _H_RED_TUBO_
#define _H_RED_TUBO_

#include <vector>
#include <unordered_map>

#include "CPU.hpp"
#include "Packet.hpp"
#include "../pe/PE.hpp"
#include "../common/Undefined.hpp"
#include "../common/Process.hpp"
#include "../common/Config.hpp"


typedef std::queue<std::tuple<Id, Packet>> buffer;

/**
 * La red tubo funciona como si fuera un solo switch que comunica todo
 *
 * */
class RedTubo: Process{
  private:
    std::unordered_map<Id, CPU_ptr> cpus;
    buffer input_buffer;

    //TODO: Creo que en vez de vector podría ser una lista enlazada ya que nos
    //da O(1) vs O(n) el vector al eliminar un elemento al inicio pero puede que
    //sea más lento al ordenar
    std::vector<std::tuple<Id, Packet>> current;

  public:
    RedTubo(std::initializer_list<std::shared_ptr<CPU>> il);
    void enviarMensaje(Id destino, MessagePE message);
    void inner_body();
    bool tuboLleno();
    void intentarAgregarPaquete();
    void entregarMensaje(Id id, Packet p);

};

#endif

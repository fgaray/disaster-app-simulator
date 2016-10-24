#ifndef _H_RED_TUBO_
#define _H_RED_TUBO_

#include <vector>
#include <unordered_map>
#include <cassert>
#include <iostream>

#include "CPU.hpp"
#include "Packet.hpp"
#include "../pe/PE.hpp"
#include "../common/Undefined.hpp"
#include "../common/Process.hpp"
#include "../common/Config.hpp"
#include "../common/RoundRobinIterator.hpp"
#include "../common/Traza.hpp"


typedef std::vector<std::tuple<Id, Packet>> buffer;



/**
 * La red tubo funciona como si fuera un solo switch que comunica todo
 *
 * */
class RedTubo: public Process{
  private:
    std::unordered_map<Id, CPU_ptr> cpus;
    buffer input_buffer;

    std::shared_ptr<Traza> traza;

    std::vector<std::tuple<Id, Packet>> current;

    // Esta tabla nos indica si el mensaje ya se encuentra siendo procesado en
    // la red y por lo tanto debemos evitar agregarlo
    std::unordered_map<Id, bool> existe;

    //Name translation table
    //Usamos esta tabla para saber el ID del pe a partir de su nombre. Dado que
    //pueden haber varios PEs con el mismo nombre (replicacion), la tabla es de
    //vectores

    // Esta tabla es "temporal" dado que necesitamos un lugar donde almacenar el
    // vector al mento de obtener el iterator
    std::unordered_map<PEName, std::vector<Id>> translation_table_tmp;


  public:
    std::unordered_map<PEName, RoundRobinIterator> translation_table;

    RedTubo(std::initializer_list<std::shared_ptr<CPU>> il);
    void enviarMensaje(Id destino, MessagePE message);
    void inner_body();
    bool tuboLleno();
    void intentarAgregarPaquete();
    void entregarMensaje(Id id, Packet p);


    /**
     * Envía el mensaje al siguiente PE con el nombre indicado. Modifica el id
     * dentro del mensaje para que sea el correspondiente al PE destinod. Se
     * envía de manera round robin.
     *
     * */
    void enviarMensaje(PEName name, MessagePE message);

};

#endif

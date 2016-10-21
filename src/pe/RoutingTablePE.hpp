#ifndef _H_ROUTINGTABLEPE_H_
#define _H_ROUTINGTABLEPE_H_

#include <unordered_map>
#include <cassert>
#include <vector>

#include "../common/IP.hpp"
#include "../common/UniqueIdGenerator.hpp"

#include "PEName.hpp"

typedef std::unordered_map<PEName, std::vector<Id>> routing_table;


/*
 * La routing table se genera de manera tal que nos permite obtener a partir del
 * nombre de un PE, los Ids a los cuales podría ir el mensaje. Son varios Ids ya
 * que se puede hacer replicación de los PE
 * */
class RoutingTablePE{
  private:
    routing_table table;
    std::unordered_map<PEName, size_t> last_selected;

  public:
    RoutingTablePE();

    /*
     * Agrega un nuevo PE con el ID especificado incluyendo las replicaciones
     * */
    void addDevice(PEName name, std::vector<Id> ids);
    Id getId(PEName id);
};


#endif

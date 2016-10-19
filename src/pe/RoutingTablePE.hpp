#ifndef _H_ROUTINGTABLEPE_H_
#define _H_ROUTINGTABLEPE_H_

#include <unordered_map>
#include <cassert>

#include "../common/IP.hpp"
#include "../common/UniqueIdGenerator.hpp"

#include "PENames.hpp"

typedef std::unordered_map<PENames, Id> routing_table;


class RoutingTablePE{
  private:
    routing_table table;

  public:
    RoutingTablePE();
    void addDevice(PENames name, Id id);
    Id getId(PENames id);
};


#endif

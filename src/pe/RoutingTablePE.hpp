#ifndef _H_ROUTINGTABLEPE_H_
#define _H_ROUTINGTABLEPE_H_

#include <unordered_map>
#include <cassert>

#include "../common/IP.hpp"
#include "../common/UniqueIdGenerator.hpp"

typedef std::unordered_map<Id, IP> routing_table;


class RoutingTablePE{
  private:
    routing_table table;

  public:
    RoutingTablePE();
    void addDevice(Id id, IP ip);
    IP getIP(Id id);

};


#endif

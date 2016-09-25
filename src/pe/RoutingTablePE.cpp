#include "RoutingTablePE.hpp"



RoutingTablePE::RoutingTablePE(){

}

void RoutingTablePE::addDevice(Id id, IP ip){
  this->table.insert(std::make_pair<>(id, ip));
}



IP RoutingTablePE::getIP(Id id){
  auto ip = this->table.find(id);
  assert(ip != this->table.end());
  return (*ip).second;
}

#include "RoutingTablePE.hpp"



RoutingTablePE::RoutingTablePE(){

}

void RoutingTablePE::addDevice(PENames name, Id id){
  this->table.insert(std::make_pair<>(name, id));
}



Id RoutingTablePE::getId(PENames name){
  auto id = this->table.find(name);
  assert(id != this->table.end());
  return (*id).second;
}

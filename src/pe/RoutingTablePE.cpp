#include "RoutingTablePE.hpp"



RoutingTablePE::RoutingTablePE(){

}

void RoutingTablePE::addDevice(PEName name, std::vector<Id> ids){
  this->table.insert(std::make_pair(name, ids));
}



Id RoutingTablePE::getId(PEName name){
  auto ids = this->table.find(name);
  assert(ids != this->table.end());
  //hacemos round robin en este punto, aqui podriamos cambiar el scheduling

  auto last = this->last_selected.find(name);

  if(last == this->last_selected.end()){
    //Es primera vez que hacemos la planificación de este PE, por lo tanto el
    //ultimo seleccionado es el index 0
    this->last_selected.insert(std::make_pair(name, 0));
    return ids->second.at(0);
  }else{
    //ya seleccionamos anteriormente el PE, sumamos +1 y sacamos el modulo % del
    //tamano del vector

    size_t nuevo = (last->second + 1) % ids->second.size();
    this->last_selected.insert(std::make_pair(name, nuevo));
    return ids->second.at(nuevo);
  }
}

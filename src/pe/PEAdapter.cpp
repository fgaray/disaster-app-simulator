#include "PEAdapter.hpp"




double  PEAdapter::getCostTime(){
	double cost = ADAPTER_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PEAdapter::nextPE(MessagePE message){
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PECollector, message)};
}


PEName PEAdapter::getName(){
  return PEName::PEAssembler;
}

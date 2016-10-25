#include "PECollector.hpp"




double  PECollector::getCostTime(){
	double cost = COLLECTOR_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PECollector::nextPE(MessagePE message){
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PEModel, message)};
}


PEName PECollector::getName(){
  return PEName::PECollector;
}

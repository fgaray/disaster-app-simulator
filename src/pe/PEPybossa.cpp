#include "PEPybossa.hpp"

double  PEPybossa::getCostTime(){
	double cost = PYBOSSA_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PEPybossa::nextPE(MessagePE message){
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PEBroker, message)};
}


PEName PEPybossa::getName(){
  return PEName::PEPybossa;
}
#include "PEFilter.hpp"



double  PEFilter::getCostTime(){
	double cost = FILTER_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PEFilter::nextPE(MessagePE message){
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PEBroker, message)};
}


PEName PEFilter::getName(){
  return PEName::PEFilter;
}

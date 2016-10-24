#include "PEPOStag.hpp"

double  PEPOStag::getCostTime(){
	double cost = POSTAGS_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PEPOStag::nextPE(MessagePE message){
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PEAssembler, message)};
}

PEName PEPOStag::getName(){
  return PEName::PEPOStag;
}

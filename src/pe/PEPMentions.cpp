#include "PEPMentions.hpp"

double  PEPMentions::getCostTime(){
	double cost = PMENTIONS_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PEPMentions::nextPE(MessagePE message){
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PEAssembler, message)};
}


PEName PEPMentions::getName(){
  return PEName::PEPMentions;
}

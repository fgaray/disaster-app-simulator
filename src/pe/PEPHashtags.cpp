#include "PEPHashtags.hpp"

double  PEPHashtags::getCostTime(){
	double cost = PHASHTAGS_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PEPHashtags::nextPE(const MessagePE &message){
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PEAssembler, message)};
}
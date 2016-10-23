#include "PENMentions.hpp"

double  PENMentions::getCostTime(){
	double cost = NMENTIONS_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PENMentions::nextPE(const MessagePE &message){
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PEAssembler, message)};
}
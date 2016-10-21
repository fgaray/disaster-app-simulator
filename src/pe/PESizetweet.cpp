#include "PESizetweet.hpp"

double  PESizetweet::getCostTime(){
	double cost = SIZETWEET_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PESizetweet::nextPE(const MessagePE &message){
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PEAssembler, message)};
}

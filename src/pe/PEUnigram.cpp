#include "PEUnigram.hpp"

double  PEUnigram::getCostTime(){
	double cost = UNIGRAM_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PEUnigram::nextPE(const MessagePE &message){
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PEAssembler, message)};
}

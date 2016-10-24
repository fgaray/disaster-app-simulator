#include "PEUnigram.hpp"

double  PEUnigram::getCostTime(){
	double cost = UNIGRAM_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PEUnigram::nextPE(MessagePE message){
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PEAssembler, message)};
}


PEName PEUnigram::getName(){
  return PEName::PEUnigram;
}

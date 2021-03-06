#include "PEBigram.hpp"




double  PEBigram::getCostTime(){
	double cost = BIGRAM_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PEBigram::nextPE(MessagePE message){
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PEAssembler, message)};
}


PEName PEBigram::getName(){
  return PEName::PEBigram;
}

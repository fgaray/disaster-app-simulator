#include "PEAssembler.hpp"




double  PEAssembler::getCostTime(){
	double cost = ASSEMBLER_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PEAssembler::nextPE(MessagePE message){
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PEFSelection, message)};
}


PEName PEAssembler::getName(){
  return PEName::PEAssembler;
}

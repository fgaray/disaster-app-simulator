#include "PEPOStag.hpp"

double  PEPOStag::getCostTime(){
	double cost = POSTAGS_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PEPOStag::nextPE(const MessagePE &message){
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PEAssembler, message)};
}

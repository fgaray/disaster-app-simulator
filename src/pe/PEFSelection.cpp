#include "PEFSelection.hpp"

double  PEFSelection::getCostTime(){
	double cost = FSELECTION_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PEFSelection::nextPE(MessagePE message){
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PETrainer, message)};
}


PEName PEFSelection::getName(){
  return PEName::PEFSelection;
}

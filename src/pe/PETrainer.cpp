#include "PETrainer.hpp"




double  PETrainer::getCostTime(){
	double cost = TRAINER_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PETrainer::nextPE(MessagePE message){
	message.setTag();
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PEModel, message)};
}


PEName PETrainer::getName(){
  return PEName::PETrainer;
}

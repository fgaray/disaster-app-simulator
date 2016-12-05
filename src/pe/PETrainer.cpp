#include "PETrainer.hpp"

static int current_precision = 0;
static int count_tag = 0;


double  PETrainer::getCostTime(){
	double cost = TRAINER_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PETrainer::nextPE(MessagePE message){
	if (message.tag){
		count_tag++;
		if (count_tag == 50){
			count_tag = 0;
			current_precision = current_precision + 0.1;
		}
	}
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PEModel, message)};
}


PEName PETrainer::getName(){
  return PEName::PETrainer;
}

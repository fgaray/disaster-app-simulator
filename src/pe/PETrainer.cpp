#include "PETrainer.hpp"

static int count_tweet = 0;


double  PETrainer::getCostTime(){
	double cost = TRAINER_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PETrainer::nextPE(MessagePE message){
	count_tweet++;
	if (count_tweet == MODEL_PRECISION)
	{
		return {std::make_tuple(PEName::END, message)};
	}
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PEModel, message)};
}


PEName PETrainer::getName(){
  return PEName::PETrainer;
}

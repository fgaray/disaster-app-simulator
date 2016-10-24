#include "PEModel.hpp"




double  PEModel::getCostTime(){
	double cost = MODEL_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PEModel::nextPE(MessagePE message){
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PEFilter, message)};
}


PEName PEModel::getName(){
  return PEName::PEModel;
}

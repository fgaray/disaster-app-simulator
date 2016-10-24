#include "PENHashtags.hpp"


double  PENHashtags::getCostTime(){
	double cost = NHASHTAGS_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PENHashtags::nextPE(MessagePE message){
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PEAssembler, message)};
}


PEName PENHashtags::getName(){
  return PEName::PENHashtags;
}

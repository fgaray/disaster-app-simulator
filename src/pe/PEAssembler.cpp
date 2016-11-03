#include "PEAssembler.hpp"




double  PEAssembler::getCostTime(){
	double cost = ASSEMBLER_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PEAssembler::nextPE(MessagePE message){
  Id mId = message.getTweetId();
	auto found = th.find(mId);
	if (found == th.end())
	{
		th.insert({mId, 1});
	}else{
		int cantM = (*found).second;
		if (cantM + 1 < 8)
		{
			(*found).second++;
		}else{
			th.erase(mId);
			MessagePE nuevomensaje(DEFAULT_MESSAGE_SIZE);
			return {std::make_tuple(PEName::PEFSelection, nuevomensaje)};
		}
	}
	return {};

  //envía el mismo mensaje sin modificar a PEAssembler
}


PEName PEAssembler::getName(){
  return PEName::PEAssembler;
}

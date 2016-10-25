#include "PEAssembler.hpp"




double  PEAssembler::getCostTime(){
	double cost = ASSEMBLER_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PEAssembler::nextPE(MessagePE message){
	MessagePE &m = message;
	MessageBroker &mensaje = static_cast<MessageBroker&>(m);
	auto found = th.find(mensaje.getIdTweet());
	if (found == th.end())
	{
		th.insert({id, 1});
	}
	else{
		int cantM = (*found).second;
		if (cantM < 8)
		{
			cantM++;
			th.insert({id, cantM});
		}
		else{
			th.erase(id);
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

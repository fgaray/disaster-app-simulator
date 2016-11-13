#include "PELastPE.hpp"


static Id device_id = 0;

double  PELastPE::getCostTime(){
	double cost = PELASTPE_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PELastPE::nextPE(MessagePE message){
  //envía el mismo mensaje sin modificar a PEAssembler
	message.setDispositivoMovil(device_id);
	device_id++;
	if (device_id == MAXIMO_MENSAJES)
	{
		device_id = 0;
	}
	return {std::make_tuple(PEName::RedMovil, message)};
}


PEName PELastPE::getName(){
  return PEName::PEAssembler;
}

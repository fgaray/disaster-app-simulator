#include "PEBroker.hpp"

static Id currentId = 0;

double  PEBroker::getCostTime(){
	double cost = BROKER_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PEBroker::nextPE(MessagePE message){
  //envía el mismo mensaje sin modificar a PEAssembler
	MessagePE mensaje(DEFAULT_MESSAGE_SIZE);
  mensaje.setTweetId(currentId);
	currentId++;
	return {std::make_tuple(PEName::PEUnigram, mensaje),
			std::make_tuple(PEName::PEBigram, mensaje),
			std::make_tuple(PEName::PEPOStag, mensaje),
			std::make_tuple(PEName::PENMentions, mensaje),
			std::make_tuple(PEName::PENHashtags, mensaje),
			std::make_tuple(PEName::PEPMentions, mensaje),
			std::make_tuple(PEName::PEPHashtags, mensaje),
			std::make_tuple(PEName::PESizetweet, mensaje)
	};
}


PEName PEBroker::getName(){
  return PEName::PEBroker;
}

#include "PEBroker.hpp"




double  PEBroker::getCostTime(){
	double cost = BROKER_COST;
	return cost;
}

std::vector<std::tuple<PEName, MessagePE>> PEBroker::nextPE(MessagePE message){
  //envía el mismo mensaje sin modificar a PEAssembler
	return {std::make_tuple(PEName::PEUnigram, message),
			std::make_tuple(PEName::PEBigram, message),
			std::make_tuple(PEName::PEPOStag, message),
			std::make_tuple(PEName::PENMentions, message),
			std::make_tuple(PEName::PENHashtags, message),
			std::make_tuple(PEName::PEPMentions, message),
			std::make_tuple(PEName::PEPHashtags, message),
			std::make_tuple(PEName::PESizetweet, message)
	};
}


PEName PEBroker::getName(){
  return PEName::PEBroker;
}

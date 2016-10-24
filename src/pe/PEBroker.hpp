#ifndef _H_PEBroker_
#define _H_PEBroker_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEName.hpp"

class PEBroker: public PE{
	private:

	public:
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(MessagePE message);
    PEName getName();
};

#endif
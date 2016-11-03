#ifndef _H_PEAssembler_
#define _H_PEAssembler_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEName.hpp"
#include <unordered_map>

class PEAssembler: public PE{
	private:
		std::unordered_map<Id, int> th;
	public:
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(MessagePE message);
    PEName getName();
};

#endif

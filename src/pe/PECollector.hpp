#ifndef _H_PECollector_
#define _H_PECollector_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEName.hpp"

class PECollector: public PE{
	private:

	public:
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(MessagePE message);
    PEName getName();
};

#endif

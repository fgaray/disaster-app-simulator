#ifndef _H_PELastPE_
#define _H_PELastPE_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEName.hpp"

class PELastPE: public PE{
	private:

	public:
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(MessagePE message);
    PEName getName();
};

#endif

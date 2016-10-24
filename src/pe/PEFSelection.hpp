#ifndef _H_PEFSelection_
#define _H_PEFSelection_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEName.hpp"

class PEFSelection: public PE{
	private:

	public:
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(MessagePE message);
    PEName getName();
};

#endif

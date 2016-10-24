#ifndef _H_PEFilter_
#define _H_PEFilter_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEName.hpp"

class PEFilter: public PE{
	private:

	public:
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(MessagePE message);
    PEName getName();
};

#endif
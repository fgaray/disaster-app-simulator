#ifndef _H_PEBigram_
#define _H_PEBigram_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEName.hpp"

class PEBigram: public PE{
	private:

	public:
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(MessagePE message);
    PEName getName();
};

#endif

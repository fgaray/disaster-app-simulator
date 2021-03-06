#ifndef _H_PEUnigram_
#define _H_PEUnigram_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEName.hpp"

class PEUnigram: public PE{
	private:

	public:
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(MessagePE message);
    PEName getName();
};

#endif

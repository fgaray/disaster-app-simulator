#ifndef _H_PEPMentions_
#define _H_PEPMentions_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEName.hpp"

class PEPMentions: public PE{
	private:

	public:
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(MessagePE message);
    PEName getName();
};

#endif

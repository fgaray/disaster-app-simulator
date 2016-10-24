#ifndef _H_PENMentions_
#define _H_PENMentions_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEName.hpp"

class PENMentions: public PE{
	private:

	public:
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(MessagePE message);
    PEName getName();
};

#endif

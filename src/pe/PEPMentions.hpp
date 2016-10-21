#ifndef _H_PEPMentions_
#define _H_PEPMentions_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEPame.hpp"

class PEPMentions: public PE{
	private:

	public:
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(const MessagePE &message);
};

#endif
#ifndef _H_PESizetweet_
#define _H_PESizetweet_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEName.hpp"

class PESizetweet: public PE{
	private:

	public:
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(const MessagePE &message);
};

#endif
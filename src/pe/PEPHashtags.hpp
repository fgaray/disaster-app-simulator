#ifndef _H_PEPHashtags_
#define _H_PEPHashtags_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEPame.hpp"

class PEPHashtags: public PE{
	private:

	public:
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(const MessagePE &message);
};

#endif
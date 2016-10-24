#ifndef _H_PEPHashtags_
#define _H_PEPHashtags_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEName.hpp"

class PEPHashtags: public PE{
	private:

	public:
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(MessagePE message);
    PEName getName();

};

#endif

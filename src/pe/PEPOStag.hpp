#ifndef _H_PEPOStag_
#define _H_PEPOStag_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEName.hpp"

class PEPOStag: public PE{
	private:

	public:
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(const MessagePE &message);
};

#endif
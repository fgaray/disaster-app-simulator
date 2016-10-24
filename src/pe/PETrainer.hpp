#ifndef _H_PETrainer_
#define _H_PETrainer_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEName.hpp"

class PETrainer: public PE{
	private:

	public:
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(MessagePE message);
    PEName getName();
};

#endif

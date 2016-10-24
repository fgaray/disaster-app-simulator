#ifndef _H_PEPybossa_
#define _H_PEPybossa_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEName.hpp"

class PEPybossa: public PE{
	private:

	public:
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(MessagePE message);
    PEName getName();
};

#endif

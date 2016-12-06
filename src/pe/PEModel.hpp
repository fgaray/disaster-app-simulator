#ifndef _H_PEModel_
#define _H_PEModel_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEName.hpp"

class PEModel: public PE{
	private:
		double precision;
	public:
		PEModel();
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(MessagePE message);
    PEName getName();
    double getPrecision();
};

#endif

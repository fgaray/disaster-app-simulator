#ifndef _H_PEUnigram_
#define _H_PEUnigram_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEName.hpp"

class PEUnigram: public PE{
	private:

	public:
		double getCostTime();
		PEName nextPE(const MessagePE &message);
};

#endif
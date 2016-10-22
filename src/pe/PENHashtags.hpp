#ifndef _H_PENHashtags_
#define _H_PENHashtags_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEName.hpp"

class PENHashtags: public PE{
	private:

	public:
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(const MessagePE &message);
};

#endif
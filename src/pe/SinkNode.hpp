#ifndef _H_SinkNode_
#define _H_SinkNode_

#include "PE.hpp"
#include "../common/Config.hpp"
#include "PEName.hpp"

/**
 * Recibe los mensajes y lo descarta. Luego de este PE no viene nadie más
 *
 * */
class SinkNode: public PE{
	private:

	public:
    SinkNode(const char *nombre);
		double getCostTime();
		std::vector<std::tuple<PEName, MessagePE>> nextPE(const MessagePE &message);
};

#endif

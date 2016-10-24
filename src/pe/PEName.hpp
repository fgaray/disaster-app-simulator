#ifndef _H_PE_NAMES_H_
#define _H_PE_NAMES_H_

#include <iostream>

// Definir los nombres de los PE aqui
enum class PEName{
	PEUnigram,
	PEBigram,
	PEPOStag,
	PENMentions,
	PEPMentions,
	PENHashtags,
	PEPHashtags,
	PESizetweet,
	PEAssembler,
	PEBroker,
	PEFilter,
	PEFSelection,
	PEModel,
  END,
  //Testing
  SinkNode,
  MockPE
};

const char* peNameToString(PEName name);

#endif

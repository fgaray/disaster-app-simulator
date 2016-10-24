#include "PEName.hpp"



const char* peNameToString(PEName name){
  switch(name){
    case PEName::PEUnigram:
	    return "PEUnigram";
      break;
    case PEName::PEBigram:
	    return "PEBigram";
      break;
    case PEName::PEPOStag:
	    return "PEPOStag";
      break;
    case PEName::PENMentions:
	    return "PENMentions";
      break;
    case PEName::PENHashtags:
	    return "PENHashtags";
      break;
    case PEName::PEPMentions:
	    return "PENMentions";
      break;
    case PEName::PEPHashtags:
	    return "PEPHashtags";
      break;
    case PEName::PESizetweet:
	    return "PESizetweet";
      break;
    case PEName::PEAssembler:
	    return "PEAssembler";
      break;
    case PEName::END:
      return "END";
      break;
    case PEName::SinkNode:
      return "SinkNode";
      break;
    case PEName::MockPE:
      return "MockPE";
      break;
    default:
      return "Caso no existe";
      break;
  }
}

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
    case PEName::PEFSelection:
      return "PEFSelection";
      break;
    case PEName::PEBroker:
      return "PEBroker";
      break;
    case PEName::PEFilter:
      return "PEFilter";
      break;
    case PEName::PEModel:
      return "PEModel";
      break;
    case PEName::PEPybossa:
      return "PEPybossa";
      break;
    case PEName::PEAdapter:
      return "PEAdapter";
      break;
    case PEName::PETrainer:
      return "PETrainer";
      break;
    case PEName::PECollector:
      return "PECollector";
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
      std::cout << static_cast<int>(name) << std::endl;
      return "Caso no existe";
      break;
  }
}

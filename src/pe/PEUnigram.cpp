#include "PEUnigram.hpp"

double  PEUnigram::getCostTime(){
	double cost = UNIGRAM_COST;
	return cost;
}

PEName PEUnigram::nextPE(const MessagePE &message){
	return PEName::PEAssembler;
}
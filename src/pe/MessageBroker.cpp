#include "MessageBroker.hpp"


MessageBroker::MessageBroker(unsigned int size, Id id): MessagePE(size){
  this->id = id;
}


Id MessageBroker::getIdTweet(){
	return this->id;
}
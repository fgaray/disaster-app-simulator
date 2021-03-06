#include "SinkNode.hpp"

double SinkNode::getCostTime(){
  return 1000;
}


std::vector<std::tuple<PEName, MessagePE>> SinkNode::nextPE(MessagePE message){
  return {std::make_tuple(PEName::END, message)};
}

PEName SinkNode::getName(){
  return PEName::SinkNode;
}

#include "RoundRobinIterator.hpp"



RoundRobinIterator::RoundRobinIterator(const std::vector<Id> &v){
  assert(v.size() != 0);
  this->max = v.size();
  this->current = 0;
}


size_t RoundRobinIterator::getNext(){
  size_t to_return = current;
  current = (current + 1) % max;
  return to_return;
}

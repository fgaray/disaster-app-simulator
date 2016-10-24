#include "RoundRobinIterator.hpp"



RoundRobinIterator::RoundRobinIterator(size_t max){
  assert(max != 0);
  this->max = max;
  this->current = 0;
}


size_t RoundRobinIterator::getNext(){
  size_t to_return = current;
  current = (current + 1) % max;
  return to_return;
}

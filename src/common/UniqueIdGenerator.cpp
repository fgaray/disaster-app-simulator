#include "UniqueIdGenerator.hpp"

static Id current_id = 0;


Id unique_id(){
  Id to_return = current_id;
  current_id++;
  return to_return;
}

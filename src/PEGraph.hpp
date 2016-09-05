#ifndef _H_PEGRAPH_
#define _H_PEGRAPH_

#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <memory>

#include "PE.hpp"

typedef std::vector<std::shared_ptr<PE>> pe_vector;
typedef std::unordered_map<size_t, pe_vector> adjacency_table;

/**
 * El grafo de PE. Indica que PE va contectado con cual.
 * */
class PEGraph{
  private:
    adjacency_table graph;
  public:
    PEGraph();
    void add_node(PE &pe, pe_vector &pes);
};

#endif

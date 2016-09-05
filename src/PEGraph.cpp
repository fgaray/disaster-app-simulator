#include "PEGraph.hpp"


PEGraph::PEGraph(){

}


void PEGraph::add_node(PE &pe, pe_vector &pes){
  this->graph.insert(std::make_pair<>(pe.getId(), pes));
}

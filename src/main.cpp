#include <iostream>
#include <memory>

#include <cppsim.hh>

#include "Source.hpp"

int main()
{
  auto sim = std::unique_ptr<simulation>(simulation::instance());
  sim->begin_simulation(new sqsDll());
  auto src = std::unique_ptr<Source>(new Source);

  // Ahora ejecutamos la simulacion
  src->activate();
  sim->run();

  // Listo!
  sim->end_simulation();
  
  return 0;
}

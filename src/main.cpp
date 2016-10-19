#include <iostream>
#include <memory>

#include <cppsim.hh>

#include "Source.hpp"
#include "common/Config.hpp"

int main()
{
  // Preparación de variables
  std::shared_ptr<RedTubo> red_tubo = std::shared_ptr<RedTubo>(new RedTubo{
      //TODO: Agregar las CPUs aqui
      });


  // Ejecución de la simulación
  auto sim = std::unique_ptr<simulation>(simulation::instance());
  sim->begin_simulation(new sqsDll());
  auto src = std::unique_ptr<Source>(new Source(END_SIM_TIME, red_tubo));

  // Ahora ejecutamos la simulacion
  src->activate();
  sim->run();

  // Listo!
  sim->end_simulation();
  
  return 0;
}

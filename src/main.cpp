#include <iostream>
#include <memory>

#include <cppsim.hh>

#include "Source.hpp"
#include "common/Config.hpp"

int main()
{
  // Preparación de variables
  auto red_tubo = handle<RedTubo>(new RedTubo{
      //TODO: Agregar las CPUs aqui
      });


  // Ejecución de la simulación
  auto sim = simulation::instance();
  sim->begin_simulation(new sqsDll());
  auto src = handle<Source>(new Source(END_SIM_TIME, red_tubo));

  //TODO: Cada componente del sistema debe registrar un callback para terminar
  //la simulación
  

  // Ahora ejecutamos la simulacion
  src->activate();
  sim->run();

  // Listo!
  sim->end_simulation();
  
  return 0;
}

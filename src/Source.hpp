#ifndef _H_SOURCE_
#define _H_SOURCE_

#include <cppsim.hh>
#include <vector>
#include "cpu/RedTubo.hpp"
#include "common/Distribution.hpp"
#include "common/Traza.hpp"

/**Esta es la fuente de todos los eventos del sistema. Probablemente sea el
 * Adapter del flujo de datos del sistema de streamming, dependiendo de cual es la aplicación que vamos a construir.*/
class Source: public process {
  protected:
    std::vector<std::function<void()>> end_callbacks;
    handle<RedTubo> red_tubo;
    std::shared_ptr<Traza> traza;

    double end_time;
    void inner_body();
    void porcentaje();

  public:
    Source(double et, handle<RedTubo> red_tubo, std::shared_ptr<Traza> traza);
    ~Source();

    /**
     * Agrega una función que va a ser llamada cuando se termine la simulación
     * */

    void addEndCallback(Process &p);

    void addEndCallback(handle<Process> p);
};

#endif

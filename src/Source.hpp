#ifndef _H_SOURCE_
#define _H_SOURCE_

#include <cppsim.hh>
#include <vector>
#include "cpu/RedTubo.hpp"

/**Esta es la fuente de todos los eventos del sistema. Probablemente sea el
 * Adapter del flujo de datos del sistema de streamming, dependiendo de cual es la aplicación que vamos a construir.*/
class Source: public process {
  protected:
    std::vector<std::function<void()>> end_callbacks;
    std::shared_ptr<RedTubo> red_tubo;

    double end_time;
    void inner_body();
    void porcentaje();

  public:
    Source(double et, std::shared_ptr<RedTubo> red_tubo);
    ~Source();

    /**
     * Agrega una función que va a ser llamada cuando se termine la simulación
     * */
    void addEndCallback(std::function<void()> callback);
};

#endif

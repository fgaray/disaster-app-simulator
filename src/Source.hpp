#ifndef _H_SOURCE_
#define _H_SOURCE_

#include <cppsim.hh>

/**Esta es la fuente de todos los eventos del sistema. Probablemente sea el
 * Adapter del flujo de datos del sistema de streamming, dependiendo de cual es la aplicación que vamos a construir.*/
class Source: public process {
  protected:
    double end_time;
    void inner_body();
    void porcentaje();
  public:
    Source(double et);
    ~Source();
};

#endif

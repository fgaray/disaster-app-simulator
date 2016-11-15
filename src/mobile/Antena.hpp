#ifndef _H_ANTENA_H_
#define _H_ANTENA_H_

#include "../common/Undefined.hpp"
#include "Device.hpp"

#include <memory>
#include <vector>
#include <math.h>

#include "../common/Process.hpp"
#include "../common/Undefined.hpp"


class Antena: public Process{
  private:
  	Id id;
    double x, y, radio;


  public:
    Antena(double _x, double _y, double _radio);
    double distancia(handle<Device> device) const;
    Id getId();
    double getRadio();

    void recibirMensaje();

    void inner_body();

};

#endif

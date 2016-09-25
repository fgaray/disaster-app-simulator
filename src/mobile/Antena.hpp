#ifndef _H_ANTENA_H_
#define _H_ANTENA_H_

#include "../common/Undefined.hpp"
#include "Device.hpp"

#include <memory>
#include <vector>

class Antena{
  private:
    double x, y, radio;

  public:
    Antena(double _x, double _y, double _radio);
    double distancia(std::shared_ptr<Device> device) const;

};

#endif

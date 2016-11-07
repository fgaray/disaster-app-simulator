#ifndef _H_MOVIMIENTO_H_
#define _H_MOVIMIENTO_H_

#include "../common/Process.hpp"
#include <functional>



typedef std::tuple<double, double, double> position;

class Movimiento: public Process{
  private:
    /**
     * Callback para notificar al dispositivo cual es su posición actual. El
     * dispositivo nos responde con la siguiente posicion a movernos
     * */
    std::function<position(double, double)> ready_callback;
    position next;
    void inner_body();

  public:
    Movimiento(std::function<position(double, double)> ready_callback);
    void setNext(position next);

};


#endif

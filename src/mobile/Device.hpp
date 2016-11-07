#ifndef _H_DEVICE_H_
#define _H_DEVICE_H_

#include "../common/Process.hpp"
#include <functional>
#include <memory>
#include <queue>

#include "../common/UniqueIdGenerator.hpp"
#include "../common/Undefined.hpp"
#include "MessageMD.hpp"
#include "Movimiento.hpp"

typedef std::function<void(Id, MessageMD)> send_callback;

class Device: public Process{
  private:
    std::function<void(std::shared_ptr<Device>)> move_device;
    send_callback send_message;
    queue<position> posiciones;
    double x, y;
    handle<Movimiento> movimiento;

    void inner_body();

  public:
    Device(std::function<void(std::shared_ptr<Device>)> move_device, send_callback send_message, std::queue<position> posiciones);
    Id getId() const;
    void agregarPosicion(double time, double _x, double _y);

    double getX() const;
    double getY() const;
    void endSimulation();

};

#endif

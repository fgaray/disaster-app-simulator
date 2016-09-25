#ifndef _H_DEVICE_H_
#define _H_DEVICE_H_

#include <process.hh>
#include <functional>
#include <memory>
#include <queue>

#include "../common/UniqueIdGenerator.hpp"
#include "../common/Undefined.hpp"
#include "MessageMD.hpp"

typedef std::function<void(Id, MessageMD)> send_callback;
typedef std::tuple<double, double, double> position;

class Device: public process{
  private:
    std::function<void(std::shared_ptr<Device>)> move_device;
    send_callback send_message;
    queue<position> posiciones;
    double x, y;

    void inner_body();

  public:
    Device(std::function<void(std::shared_ptr<Device>)> _move_device, send_callback _send_message);
    Id getId() const;
    void agregarPosicion(double time, double _x, double _y);

    double getX() const;
    double getY() const;

};

#endif

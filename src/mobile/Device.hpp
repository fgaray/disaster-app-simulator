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
#include "PacketMD.hpp"
#include "Antena.hpp"
#include "../common/Config.hpp"

typedef std::function<void(MessageMD)> send_callback;
typedef std::vector<std::tuple<Id, Id, PacketMD>> buffer_device;

class Device: public Process{
  private:
    std::function<void(Device*)> move_device;
    send_callback send_message;
    queue<position> posiciones;
    queue<MessageMD> mensajes;
    double x, y;
    handle<Movimiento> movimiento;
    Id id;
    buffer_device paquetes;
    void inner_body();

  public:
    Device(std::queue<position> posiciones);
    Id getId() const;
    void agregarPosicion(double time, double _x, double _y);

    double getX() const;
    double getY() const;
    void endSimulation();

    void recibirPaquetesAntena(Id id_antena, PacketMD p); 
    void setSendCallback(send_callback callback);
    void setMoveCallback(std::function<void(Device*)> callback);
    void iniciar_mov();

};

#endif

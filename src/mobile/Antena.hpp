#ifndef _H_ANTENA_H_
#define _H_ANTENA_H_

#include "../common/Undefined.hpp"
#include "Device.hpp"
#include "PacketMD.hpp"
#include "MessageMD.hpp"
#include "Network3G.hpp"

#include <unordered_map>
#include <memory>
#include <vector>
#include <math.h>
#include <iterator>
#include <functional>

#include "../common/Process.hpp"
//#include "../common/Undefined.hpp"
#include "../common/Config.hpp"


class Antena: public Process{
  private:
  	Id id;
    double x, y, radio;
    //buffer_antena input_buffer;
    //std::unordered_map<Id, MessageMD> cola_ms;
    std::queue<std::tuple<Id, MessageMD>> cola_ms;
    std::function<void(MessageMD)> responder_mensaje;
    handle<Network3G> red_movil;

  public:
    Antena(double _x, double _y, double _radio);
    double distancia(handle<Device> device) const;
    Id getId();
    double getRadio();

    void recibirMessage(Id id_device, MessageMD m);

    void inner_body();

    std::function<void(MessageMD)> getAntenaResponderCallback();

    void setResponderCallback(std::function<void(MessageMD)> callback);
    void setRedMovil(handle<Network3G> red_movil);

};

#endif

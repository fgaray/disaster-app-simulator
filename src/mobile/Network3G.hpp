#ifndef _H_NETWORK3G_H_
#define _H_NETWORK3G_H_

#include <unordered_map>
#include <vector>
#include <memory>
#include <functional>

#include "../common/IP.hpp"
#include "../common/Process.hpp"
#include "../common/Undefined.hpp"
#include "../common/UniqueIdGenerator.hpp"

#include "MessageMD.hpp"
#include "Antena.hpp"
#include "Device.hpp"


class Network3G: public Process{
  private:

    std::unordered_map<Id, std::shared_ptr<Antena>> devices_antenas;

    std::unordered_map<Id, std::shared_ptr<Device>> devices;

    void inner_body();

  public:
    Network3G();

    void enviarMensajeHaciaMD(Id hacia, MessageMD m);
    void enviarMensajeHaciaCluster(Id desde, MessageMD m);

    std::function<void(Id, MessageMD)> getSendCallback();
    std::function<void(std::shared_ptr<Device>)> getMoveCallback();


};

#endif

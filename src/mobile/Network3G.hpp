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
#include "PacketMD.hpp"

typedef std::vector<std::tuple<Id, Id, PacketMD>> buffer2;

class Network3G: public Process{
  private:

    std::unordered_map<Id, handle<Antena>> devices_antenas;
    std::unordered_map<Id, handle<Antena>> antenas;

    std::vector<std::tuple<Id, Id, PacketMD>> current;

    std::unordered_map<Id, bool> existe;

    buffer2 input_buffer;
    buffer2 red_buffer;
    buffer2 output_buffer;

    //Solo para constructor de la red (asignar device a antenas)
    //std::unordered_map<Id, std::shared_ptr<Device>> devices_tmp;

    void inner_body();

  public:
    Network3G(std::initializer_list<handle<Device>> dv, std::initializer_list<handle<Antena>> al);

    //Funcion que divide mensaje original y envia paquetes a antena

    //Funcion que recibe paquetes random sueltos y los envia a la nueva antena
    //(Cuando el device se cambia de antena)

    void enviarMensajeHaciaMD(Id hacia, MessageMD m);
    void enviarMensajeAntena(Id antena, Id device, MessageMD m);
    void enviarMensajeHaciaCluster(MessageMD m);
    void entregarMensaje(Id id_antena, Id id_device, PacketMD p);
    void intentarAgregarPaquete();
    bool redSaturada();

    std::function<void(MessageMD)> getSendCallback();
    std::function<void(std::shared_ptr<Device>)> getMoveCallback();

    std::function<void(Device*)> getCallbackNotificarMovimiento();

    void notificarMovimientoDevice(Device *d);

};

#endif

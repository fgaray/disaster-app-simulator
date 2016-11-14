#ifndef _H_PACKETMD_
#define _H_PACKETMD_

#include "MessageMD.hpp"
#include "../common/Undefined.hpp"
#include "../common/Process.hpp"
#include "../common/Config.hpp"

#include <memory>

/**
 * Un mensaje es dividido en distintos paquetes de acuerdo a la configuración
 * PACKET_SIZE
 * */
class PacketMD{
  private:
    MessageMD message;
    unsigned int number, size;
    bool last;

    // es el tiempo que le queda para seguir en el tubo, depende de los bits por
    // segundo 
    double remaining_time;
  public:
    /*
     * @param message El mensaje que fue dividido en paquetes
     * @param number El número de paquete para este mensaje
     * @param size El tamaño en bits de este paquete
     * @param last Si es el último paquete que componen el mensaje
     *
     * */
    Packet(MessagePE message, unsigned int number, bool last);

    unsigned int getMessageSize();
    unsigned int getPacketSize();
    MessageMD getMessage();
    bool isLast();
    void setLast(bool last);
    unsigned int getNumber();

    /**
     * Resta el tiempo t al remaining time de este paquete
     * */
    void restarTiempo(double t);

    double getRemainingTime();

    bool operator<(const PacketMD& p) const;

};


#endif
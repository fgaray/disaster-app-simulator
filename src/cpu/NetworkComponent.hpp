#ifndef _H_NETWORK_COMPONENT_H_
#define _H_NETWORK_COMPONENT_H_ 

#include <string>
#include <queue>
#include <tuple>
#include <memory>

#include "../common/IP.hpp"
#include "../common/Undefined.hpp"
#include "../pe/MessagePE.hpp"
#include "../pe/PE.hpp"
#include <process.hh>

typedef tuple<MessagePE, IP> element;
typedef std::queue<element> buffer;

class NetworkComponent: public process{
  protected:
    IP ip;
    bool run;

    //El buffer de mensajes recibidos. Para cada mensaje que llega se guarda en
    //este buffer donde se le asigna 
    buffer input_buffer;

  public:
    NetworkComponent(std::string name, IP _ip);
    IP getIP();

    void inner_body();

    void end_run();

    void receiveMessage(MessagePE pe, IP destino);
    void enviarMensaje(MessagePE pe, IP destino);

    virtual void component_inner_body(element e) = 0;
};

#endif

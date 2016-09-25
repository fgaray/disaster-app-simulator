#ifndef _H_SWITCH_H_
#define _H_SWITCH_H

#include "NetworkComponent.hpp"

class Switch: public NetworkComponent{

  public:
    Switch(std::string name, IP _ip);

    void component_inner_body(element e);

};

#endif

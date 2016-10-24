#ifndef _H_PROCESS_H_
#define _H_PROCESS_H_

#include <process.hh>
#include "Traza.hpp"
#include <memory>

class Process: public process{
  protected:
    bool run;
    std::string name;
    std::shared_ptr<Traza> traza;

  public:
    Process(const std::string &name);
    void endSimulation();
    function<void()> getEndCallback();
    void setTraza(std::shared_ptr<Traza> traza);
};

#endif

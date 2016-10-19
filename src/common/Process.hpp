#ifndef _H_PROCESS_H_
#define _H_PROCESS_H_

#include <process.hh>

class Process: public process{
  protected:
    bool run;

  public:
    Process(const std::string &name);

    void endSimulation();

};

#endif

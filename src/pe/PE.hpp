#ifndef _H_PE_
#define _H_PE_

#include <cstdio>
#include <string>


/**
 * La instanciación de esta clase NO es thread safe.
 * */
class PE{
  private:
    size_t id;
    std::string nombre;
  public:
    PE(const std::string &nombre_pe);
    size_t getId();

};

#endif

#ifndef _H_UNDEFINED_H_
#define _H_UNDEFINED_H_

#include <exception>
#include <string>

#define UNDEFINED Undefined(__func__)

class Undefined: public std::exception{
  private:
    std::string nombre;

  public:
    Undefined(const char *nombre_fn);
    const char* what();

};


#endif

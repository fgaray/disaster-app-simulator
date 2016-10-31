#ifndef _H_TRAZA_H_
#define _H_TRAZA_H_

#include <iostream>
#include <memory>
#include <cstdio>
#include <sstream>

#define SALIDA std::cout
#define COLOR true
#include <string>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Ejemplo
//  printf(ANSI_COLOR_RED     "This text is RED!"     ANSI_COLOR_RESET "\n");

class Traza{
  private:

  public:
    Traza();

    void punto(double time, const std::string &str);
    void puntoCPU(double time, const std::string &str);
    void puntoRedTubo(double time, const std::string &str);
    void puntoFin(double time, const std::string &str);
    void puntoSource(double time, const std::string &str);
    void puntoCore(double time, const std::string &str);

    void punto(double time, const std::stringstream &str);
    void puntoCPU(double time, const std::stringstream &str);
    void puntoRedTubo(double time, const std::stringstream &str);
    void puntoFin(double time, const std::stringstream &str);
    void puntoSource(double time, const std::stringstream &str);
    void puntoCore(double time, const std::stringstream &str);



};



#endif

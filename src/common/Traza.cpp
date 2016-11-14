#include "Traza.hpp"


Traza::Traza(){
  
}

void Traza::punto(double time, const std::string &str){
  SALIDA << "[" << time << "] " << str << std::endl;
}


void Traza::puntoRedTubo(double time, const std::string &str){
  SALIDA << ANSI_COLOR_YELLOW << "[" << time << "] " << str << ANSI_COLOR_RESET << std::endl;
}

void Traza::puntoCPU(double time, const std::string &str){
  SALIDA << ANSI_COLOR_GREEN << "[" << time << "] " << str << ANSI_COLOR_RESET << std::endl;
}

void Traza::puntoFin(double time, const std::string &str){
  SALIDA << ANSI_COLOR_RED << "[" << time << "] " << str << ANSI_COLOR_RESET << std::endl;
}

void Traza::puntoSource(double time, const std::string &str){
  SALIDA << ANSI_COLOR_CYAN << "[" << time << "] " << str << ANSI_COLOR_RESET << std::endl;
}

void Traza::puntoCore(double time, const std::string &str){
  SALIDA << ANSI_COLOR_MAGENTA << "[" << time << "] " << str << ANSI_COLOR_RESET << std::endl;
}

void Traza::puntoRed3G(double time, const std::string &str){
  SALIDA << ANSI_COLOR_BLUE << "[" << time << "]" << str << ANSI_COLOR_BLUE << std::endl;
}


void Traza::puntoRedTubo(double time, const std::stringstream &str){
  this->puntoRedTubo(time, str.str());
}

void Traza::puntoCPU(double time, const std::stringstream &str){
  this->puntoCPU(time, str.str());
}

void Traza::puntoFin(double time, const std::stringstream &str){
  this->puntoFin(time, str.str());
}

void Traza::puntoSource(double time, const std::stringstream &str){
  this->puntoSource(time, str.str());
}

void Traza::puntoCore(double time, const std::stringstream &str){
  this->puntoCore(time, str.str());
}

void Traza::puntoRed3G(double time, const std::stringstream &str){
  this->puntoRed3G(time, str.str());
}

#include "Traza.hpp"

#include <fstream>
#include <iostream>




trazas_devices parsear_traza(const char *archivo){
  trazas q;
  trazas_devices trz;

  std::ifstream infile(archivo);

  std::string linea;
  Id id_anterior = 999999;

  std::cout << "Leyendo traza..." << std::flush;

  while(infile >> linea){

    auto ts = tokens(linea);

    Id id = std::stoi(ts[0]);
    double tiempo = std::stof(ts[2]);
    double x = std::stof(ts[3]);
    double y = std::stof(ts[4]);

    q.push(std::make_tuple(tiempo, x, y));

    if(id_anterior != id){
      //nuevo id conocido, debemos guardar en la tabla hash
      trz.insert({id_anterior, q});
      q = std::queue<std::tuple<double, double, double>>();
    }
  }

  std::cout << "listo" << std::endl;

  return trz;
}


std::vector<std::string> tokens(std::string str){
  std::vector<std::string> all;

  std::string current;

  for(size_t i = 0; i < str.size(); i++){
    char c = str[i];
    if(c == ','){
      all.push_back(current);
      current = "";
    }else{
      current += c;
    }
  }

  all.push_back(current);

  return all;
}

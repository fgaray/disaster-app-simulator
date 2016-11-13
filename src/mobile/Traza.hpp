#ifndef _H_TRAZA_PARSER_H_
#define _H_TRAZA_PARSER_H_


#include <unordered_map>
#include <queue>
#include "../common/UniqueIdGenerator.hpp"


typedef std::queue<std::tuple<double, double, double>> trazas;
typedef std::unordered_map<Id, trazas> trazas_devices;


/**
 * A partir del nombre del archivo, lee el archivo CSV para obtener las
 * posiciones x e y en el tiempo. Cada posicicon es una tupla con el (tiempo, x, y)
 *
 * */
trazas_devices parsear_traza(const char *archivo);

std::vector<std::string> tokens(std::string str);


#endif

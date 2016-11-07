#ifndef _H_TRAZA_H_
#define _H_TRAZA_H_


#include <unordered_map>
#include <queue>
#include "../common/UniqueIdGenerator.hpp"

/**
 * A partir del nombre del archivo, lee el archivo CSV para obtener las
 * posiciones x e y en el tiempo. Cada posicicon es una tupla con el (tiempo, x, y)
 *
 * */
std::vector<std::queue<std::tuple<double, double, double>>> parsear_traza(const char *archivo);



#endif

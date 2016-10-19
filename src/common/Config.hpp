#ifndef _CONFIG_H_
#define _CONFIG_H_

// 1000 = 1s
// Mil equivale a 1 segundo, para dejar definida nuestra línea base

// Cuanto se demora cada paquete en viajar por la red
const double LATENCIA_RED = 100;


// El tiempo en que la simulación termina de ejecutar todo
const double END_SIM_TIME = 10000;


// Tamaño del paquete maximo a enviar por la red en bits
const unsigned int PACKET_SIZE = 100;

#endif

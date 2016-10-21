#ifndef _CONFIG_H_
#define _CONFIG_H_

// 1000 = 1s
// Mil equivale a 1 segundo, para dejar definida nuestra línea base

// Cuanto se demora cada paquete en viajar por la red
const double LATENCIA_RED = 100;
const double UNIGRAM_COST = 1500;
const double BIGRAM_COST = 1500;
const double POSTAGS_COST = 1500; //Creo que este proceso es el más costoso o no? (Tito?)
const double NMENTIONS_COST = 1500;
const double PMENTIONS_COST = 1500;
const double NHASHTAGS_COST = 1500;
const double PHASHTAGS_COST = 1500;
const double SIZETWEET_COST = 1500;


// El tiempo en que la simulación termina de ejecutar todo
const double END_SIM_TIME = 10000;


// Tamaño del paquete maximo a enviar por la red en bits
const unsigned int PACKET_SIZE = 100;

#endif

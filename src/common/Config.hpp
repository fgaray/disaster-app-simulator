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
const double BROKER_COST = 0;
const double FILTER_COST = 0;
const double ASSEMBLER_COST = 1500;
const double FSELECTION_COST = 1500;
const double MODEL_COST = 2000;
const double PYBOSSA_COST = 1500;
const double TRAINER_COST = 1500;
const double ADAPTER_COST = 1500;
const double COLLECTOR_COST = 1500;

const double TWEET_PER_SECOND = 2;
const double AMOUNT_OF_TWEETS = 10000;

// El tiempo en que la simulación termina de ejecutar todo
const double END_SIM_TIME = 100000;

const unsigned int MAXIMO_MENSAJES = 10;


// Tamaño del paquete maximo a enviar por la red en bits
const unsigned int PACKET_SIZE = 100;


// En bps
const unsigned int VELOCIDAD_RED_TUBO = 10000*1000; // 1MB/s

//Este es el ancho de banda en un instante dentro de la red en bits. Lo usamos
//para identificar cuanto es el máximo de paquetes que pueden estar dentro de la
//red en un momento.
const unsigned int ANCHO_BANDA_INSTANTE = 1000;

// En bitss
const unsigned int DEFAULT_MESSAGE_SIZE = 200;

#endif

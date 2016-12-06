// exponential_distribution
#include "Distribution.hpp"

Distribution::Distribution(double _cantidad_tweets, double _lambda){
	this->cantidad_tweets = _cantidad_tweets;
	this->lambda = _lambda;
}

double Distribution::GeneradorExp(){
	//No se donde colocar esta linea...
	std::default_random_engine generator;
	std::exponential_distribution<double> distribution(lambda);

    double number = distribution(generator);
    return number;
}

double Distribution::GeneradorNorm(){
	//No se donde colocar esta linea...
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(cantidad_tweets,lambda);

    double number = distribution(generator);
    return number;
}
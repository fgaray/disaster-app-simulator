// exponential_distribution
#include "Distribution.hpp"

Distribution::Distribution(double _cantidad_tweets, double _lambda){
	this->cantidad_tweets = _cantidad_tweets;
	this->lambda = _lambda;
}

double Distribution::GeneradorExp(){
	//No se donde colocar esta linea...
	std::exponential_distribution<double> distribution(lambda);

    double number = distribution(generator);
    return number;
}

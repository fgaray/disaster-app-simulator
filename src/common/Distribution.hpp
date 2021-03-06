#ifndef _H_Distribution
#define _H_Distribution

#include <iostream>
#include <random>
#include "../common/Config.hpp"

/**
 * Una IPv4
 * */
class Distribution{
  private:
    double cantidad_tweets;  // number of experiments
    std::default_random_engine generator;
    double lambda;
  public:
  	Distribution(double _cantidad_tweets, double _lambda);
    double GeneradorExp();

};

#endif
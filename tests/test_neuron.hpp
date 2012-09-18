#ifndef TEST_NEURON
#define TEST_NEURON

#include <iostream>
#include <map>
#include <fstream>
#include "heavy_neuron.hpp"
#include "activation.hpp"

double weighted_sum(double, double, double, double, double, double, double);

void test_neuron(std::map<std::string,std::string>&);

#endif

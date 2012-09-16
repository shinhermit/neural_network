#ifndef TEST_BACKPROP
#define TEST_BACKPROP

#include "learning.hpp"
#include "models.hpp"
#include "easyContainers.hpp"

#include <cstring>
#include <fstream>
#include <sstream>

/**
 *@brief evaluates the network with the inputs of some examples of the patterns set, and displays the outputs of the network
 *@param net the neural network
 *@param set the set of examples
 *@param how_many the number of examples to evaluate
 */
void evaluate_few_examples(network&, pattern_set&, int);

/**
 *@brief
 *@param args parameter specified by the user (parsed from command line)
 */
void test_backprop(std::vector<std::string>&);

#endif

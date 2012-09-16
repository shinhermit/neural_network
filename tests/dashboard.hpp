#ifndef DASHBOARD
#define DASHBOARD

#include <cstring>
#include <string>
#include <vector>
#include "funcs.hpp"
#include "learning.hpp"
#include "easyContainers.hpp"

#include "test_unit.hpp"
#include "test_synaptic.hpp"
#include "test_synaptics.hpp"
#include "test_neuron.hpp"
#include "test_layer.hpp"
#include "test_network.hpp"
#include "test_MLP_model.hpp"
#include "test_MLP.hpp"
#include "test_pattern.hpp"
#include "test_pattern_set.hpp"
#include "test_backprop.hpp"

/**
 *@brief
 *Shows a contextual help with the defferent command line options
 */
void usage();

/**
 *@brief displays the menu
 *liste of available programs
 */
void show_menu();

/**
 *@brief finds the program to execute in the command line arguments
 *@param  argc num of arguments of the command line. Propagates the int argc argument of the function main()
 *@param  argv text values of the arguments of the command line. Propagates the char** argv argument of the function main()
 *@param prog DR variable where we store the result (the specified program [-p program])
 *@param args DR variable where we store the arguments (everything after -a
 *@return bool true if all options are valid, false elsewise (must show help ie function usage() )
 */
bool parse_cmd_line(int, char**, std::string&, std::string & program, std::vector<std::string> & args);

/**
 *@brief execute the selected program
 *@param c choice of the user
 *@param argc num of passed arguments
 *@param char** values of passed arguments
 *@return bool quit state, true if the user chose to exit, false eslwise.
 *
 */
bool apply_choice(std::string c, int argc, int begin_at, char** argv);

#endif

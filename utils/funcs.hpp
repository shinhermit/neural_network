#ifndef FUNCS
#define FUNCS

#include <cmath>
#include <cstring>
#include <map>
#include "heavy_network.hpp"

namespace funcs
{

  void print_output(network&);

  int find_args(int, char**, std::string="-a");

  void parse_cmd_line(int, char**, std::map<std::string,std::string>&);

};

#endif

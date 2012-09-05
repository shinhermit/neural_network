#ifndef MODELS
#define MODELS

#include "heavy_network.hpp"

namespace models
{
  /**
   *@brief creates Multi-Layer Perceptron like connections in a network that already has layers.
   *@param net layered network we want to connect as an MLP
   */
  void connect_MLP(network&);

  /**
   *@brief builds a heavy Multi-Layer Percetron like network from scratch
   *Any pre-existant content will be cleared
   *The architecture is input_layer - hidden_layer - output_layer
   *@param num_of_inputs
   *@param num_of_input_cells
   *@param num_of_hidden
   *@param num_of_ouput
   */
  void build_heavy_MLP(network&, int,int, int, int);
};

#endif

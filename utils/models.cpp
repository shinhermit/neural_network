#include "models.hpp"

namespace models
{
  void connect_MLP(network & net){
    int j, i, p, k, num_of_layers, num_of_neurons, num_of_preds;

    net.clear_connections();

    num_of_layers = net.size();
    for(j=1; j<num_of_layers; j++){

      num_of_neurons = net[j]->size();
      for(i=0; i<num_of_neurons; i++){

	p=j-1;
	num_of_preds = net[p]->size();
	for(k=0; k<num_of_preds; k++){
	  net.connect(p,k, j,i);
	}
      }
    }
  }

  void build_heavy_MLP(network & net, int num_of_inputs, int num_of_input_cells, int num_of_hidden, int num_of_output){

    net.clear();

    net << new heavy_layer(num_of_input_cells, num_of_inputs);
    net << new heavy_layer(num_of_hidden, num_of_input_cells);
    net << new heavy_layer(num_of_output, num_of_hidden);

    connect_MLP(net);
  }
};


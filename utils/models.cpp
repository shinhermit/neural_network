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

  void build_heavy_MLP(network & net, int num_of_inputs, int hidden_layer_size, int output_layer_size){

    net.clear();

    net << new heavy_layer(hidden_layer_size, num_of_inputs);
    net << new heavy_layer(output_layer_size, hidden_layer_size);

    connect_MLP(net);
  }
};


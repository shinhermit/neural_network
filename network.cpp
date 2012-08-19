#include "network.hpp"

network::network(){}

network::network(int layers_num, int neuron_per_layer, int inputs_per_neuron){
  int i, size;
  perceptron p;

  for(i=0; i<layers_num; i++){
    p = perceptron(neuron_per_layer, inputs_per_neuron);
    _layers.push_back(p);
    _connexions.push_back( std::list<synaptic>() );
  }
}

network::network(const network & source):_layers(source._layers), _connexions(source._connexions){
}

network::~network(){
}

network & network::operator=(const network & source){
  _layers = source._layers;
  _connexions = source._connexions;
  return *this;
}


void network::add_neuron(int layer, neuron neurone){
  int num_of_layers;

  num_of_layers = _layers.size();
  if(0<=layer && layer<num_of_layers){
    _layers[layer].add(neurone);
  }
  else throw "network::add_neuron(int,neuron) : invalid layer index.";
}

void network::rmv_neuron(int layer, int pos){
  int num_of_layers, theLayer_size;

  num_of_layers = _layers.size();
  if(0<=layer && layer<num_of_layers){
    theLayer_size = _layers[layer].size();
    if(0<=pos && pos < theLayer_size){
      _layers[layer].erase(_layers.begin()+pos);
      disconnect_all( unit(layer, pos) );
    }
    else throw "network::rmv_neuron(int,int) : invalid neuron position.";
  }
  else throw "network::rmv_neuron(int,int) : invalid layer index.";
}

void network::add_layer(perceptron layer){
  _layer.push_back(layer);
  _connexions.push_back( std::list<synaptic>() );
}

void network::rmv_layer(int layer){
  int num_of_layers, size, pos;

  num_of_layers = _layers.size();
  if(0<=layer && layer < num_of_layers){
    size = _layers[layer].size();
    for(pos=0; pos<size; pos++){
      disconnect_all( unit(layer, pos) );
    }
    _layers.erase(layer);
    _connexions.erase(layer);
  }
}

void network::add_layers(int how_many, int layer_size, int neuron_size){
  int i;
  perceptron layer;

  for(i=0; i<how_many; i++){
    layer = perceptron(layer_size, neuron_size);
    _layers.push_back(layer);
    _connexions.push_back( std::list<synaptic>() );
  }
}

void network::rmv_layers(int begin, int end){
  int num_of_layers, layer;
  layer = begin;
  while(layer <= end && layer < num_of_layers){
    rmv_layer(layer);
    layer++;
  }
}

bool valid_unit(unit cell){
  int num_of_layers, theLayer_size;
  num_of_layers = _layers.size();
  if(0 <= cell.layer() && cell.layer() < num_of_layers){
    theLayer_size = _layers[cell.layer()].size();
    if(0 <= cell.pos() && cell.pos() < theLayer_size)
      return true
  }
  else return false;
}

bool network::registered_connection(synaptic synapse){
  int layer, num_of_synapses;
  synaptics::iterator it;
  bool found;
  
    found = false;
  if( valid_unit(src) && valid_unit(dst) ){
    layer = dst.layer();
    num_of_synapses = _conexions[layer].size();
    it = _connexions[layer].begin();
    while(it != _connexions[layer].end() && !found){
      if(*it == synapse)
	found = true;
      else
	it++;
    }
  }
  return found;
}

bool network::are_connected(unit src, unit dst){
  return registered_connection( synaptic(src, dst) );
}

void network::connect(unit src, unit dst){
  int layer;

  if( valid_unit(src) && valid_unit(dst) ){
    synaptic synapse(src, dst);
    if( !registered_connection(synapse) ){
      layer = synapse.layer();
      _connexions[layer].push_back(synapse);
    }
  }
  else throw "network::connect(unit,unit) : a given unit does not identify any cell of this network.";
}

void network::connect(int src_layer, int src_pos, int dst_layer, int dst_pos){
  connect( unit(src_layer, src_pos), unit(dst_layer, dst_pos) );
}

void network::disconnect(synaptic synapse){
  int layer;

  if( registered_connection(synapse) ){
    layer = synapse.layer();
    _connexions[layer].erase(synapse);
  }
  else throw "network::connect(synaptic) : given synapse argument not found in the network.";
}

void network::disconnect(unit src, unit dst){
  try{
    disconnect( synaptic(src, dst) );
  }
  catch(std::string){
    throw "network::connect(unit,unit) : a given unit does not identify any cell of this network.";
  }
}

void network::disconnect_all(unit cell){
  int layer, num_of_layers;
  synaptics::iterator it;

  if( valid_unit(cell) ){
    //every incoming (and reccurent) connections (ie, registered in given cell's layer)
    layer = cell.layer();
    for(it=_connexions[layer].begin(); it!=_connexions[layer].end(); it++){
      if( it->dest() == cell ){
	disconnect(*it);
      }
    }

    //every outgoing connections (ie, registered in a layer after given cell's layer)
    layer++;
    num_of_layers = _layers.size();
    while(layer < num_of_layers){
      for(it=_connexions[layer].begin(); it!=_connexions[layer].end(); it++){
	if( it->source() == cell ){
	  disconnect(*it);
	}
      }      
      layer++;
    }
  }
  else throw "network::disconnect_all(unit) : given unit does not identify any neuron of the network.";
}

void network::synaptic_injection(int layer_index){
  int num_of_layers, index;
  perceptron * dst_layer;
  perceptron * src_layer;
  neuron* dst_neuron;
  neuron* src_neuron;
  synaptics* connections;
  synaptics::iterator it;

  num_of_layers = _layers.size();
  if(0 <= layer_index && layer_index < num_of_layers){
    dest_layer = & _layer[layer_index];
    connections = & _connexions[layer_index];
    for(it=connections->begin(); it!=connections->end(); it++){
      //incoming neuron
      index = it->dest().pos();
      dst_neuron = & *dest_layer[index];

      //outgoing neuron
      index = it->source().layer();
      src_layer = & _layers[index];
      index = it->source().pos();
      src_neuron = & *src_layer[index];

      //injection
      dst_neuron->receive( src_neuron->output() );
    }
  }
  else throw "network::synaptic_injection(int) : invalid layer index.";
}

std::vector<unit> network::succ(unit & src_unit){
  int layer_index, num_of_layers;
  synaptics::iterator it;
  std::vector<unit> receivers;

  if( valid_unit(src_unit) ){
    layer_index = src_unit.layer();
    while(layer_index < num_of_layers){
      for(it=_connexion[layer_index].begin(); it!=_connexions[layer_index].end(); it++){
	if(it->source() == src_unit){
	  receivers.push_back( it->dest() );
	}
      }
      layer_index ++;
    }
    return receivers;
  }
  else throw "network::succ(unit) : invalid given unit object.";
}

std::vector<unit> network::succ(int src_layer, int src_pos){
  try{
    return succ( unit(src_layer, src_pos) );
  }
  catch(std::string){
    throw "network::succ(int,int) : invalid index given as parameter. No unit described.";
  }
}

std::vector<unit> network::pred(unit & dst_unit){
  int layer_index;
  synaptics::iterator it;
  std::vector<unit> senders;

  if( valid_unit(dst_unit) ){
    layer_index = dst_unit.layer();
    while(layer_index >= 0){
      for(it=_connexion[layer_index].begin(); it!=_connexions[layer_index].end(); it++){
	if(it->dest() == dst_unit){
	  senders.push_back( it->source() );
	}
      }
      layer_index --;
    }
    return senders;
  }
  else throw "network::succ(unit) : invalid given unit object.";
}

std::vector<unit> network::pred(int dst_layer, int dst_pos){
  try{
    return pred( unit(dst_layer, dst_pos) );
  }
  catch(std::string){
    throw "network::pred(int,int) : invalid passed argument. Invalid index.";
  }
}

void network::receive(double value){
  //couche d'entrée = couche 0
  _layers[0].receive(value);
}

void network::receive(std::vector<double> data){
  //couche d'entrée = couche 0
  _layers[0].receive(data);
}

void network::evaluate(){
  int i, num_of_layers;

  num_of_layers = _layers.size();
  for(i=0; i < num_of_layers; i++){
    _layers[i].evaluate();
  }
}

std::vector<float> network::output(){
  int last;

  //couche de sortie = dernière couche
  last = _layers.size() - 1;
  return _layers[last].output();
}

void network::reset(){
  int i, num_of_layers;

  num_of_layers = _layers.num_of_layers();
  for(i=0; i < num_of_layers; i++){
    _layers[i].reset();
  }
}

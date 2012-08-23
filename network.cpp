#include "network.hpp"

network::network(){}

network::network(int layers_num, int neurons_per_layer, int inputs_per_neuron){
  int i;
  perceptron p;

  for(i=0; i<layers_num; i++){
    p = perceptron(neurons_per_layer, inputs_per_neuron);
    _layers.push_back(p);
    _connexions.push_back( synaptics() );
  }
}

network::network(const network & source):_layers(source._layers), _connexions(source._connexions){
}

network::~network(){}

network & network::operator=(const network & source){
  _layers = source._layers;
  _connexions = source._connexions;
  return *this;
}

network & network::operator>>(std::ostream & out){
  int i, size;

  size = _layers.size();
  out<<"----------"<<std::endl;
  for(i=0; i < size-1; i++){
    out << _layers[i] <<std::endl;
    _connexions[i]>>out;
    out <<std::endl<<std::endl;
  }
  if(i == size-1){
    out << _layers[i] <<std::endl;
    _connexions[i]>>out;
    out<<std::endl;
  }
  out<<"----------"<<std::endl;
  return *this;
}

std::ostream & operator<<(std::ostream & out, network & net){
  net >> out;
  return out;
}


network & network::operator<<(perceptron layer){
  _layers.push_back(layer);
  _connexions.push_back( synaptics() );
  return *this;
}

network & network::operator<<(double value){
  _layers[0] << value;
  return *this;
}

network & network::operator<<(std::vector<double> & data){
  _layers[0] << data;
  return *this;
}


void network::add_neuron(int layer, neuron cell){
  int num_of_layers;

  num_of_layers = _layers.size();
  if(0<=layer && layer<num_of_layers){
    _layers[layer].add(cell);
  }
  else throw std::string("network::add_neuron(int,neuron) : invalid layer index.");
}

void network::rmv_neuron(int layer, int pos){
  int num_of_layers, theLayer_size;

  num_of_layers = _layers.size();
  if(0<=layer && layer<num_of_layers){
    theLayer_size = _layers[layer].size();
    if(0<=pos && pos < theLayer_size){
      _layers[layer].remove(pos);
      disconnect_all( unit(layer, pos) );
    }
    else throw std::string("network::rmv_neuron(int,int) : invalid neuron position.");
  }
  else throw std::string("network::rmv_neuron(int,int) : invalid layer index.");
}

void network::add_layer(perceptron layer, int pos){
  int size;

  size = _layers.size();
  if(pos == -1 || abs(pos) >= size){
    _layers.push_back(layer);
    _connexions.push_back( synaptics() );
  }
  else{
    pos = abs(pos);
    _layers.insert(_layers.begin()+pos, layer);
    _connexions.insert(_connexions.begin()+pos, synaptics());
  }
}

void network::rmv_layer(int layer){
  int num_of_layers, size, pos;

  num_of_layers = _layers.size();
  if(0<=layer && layer < num_of_layers){
    size = _layers[layer].size();
    for(pos=0; pos<size; pos++){
      disconnect_all( unit(layer, pos) );
    }
    _layers.erase(_layers.begin()+layer);
    _connexions.erase(_connexions.begin()+layer);
  }
}

void network::add_layers(int how_many, int layer_size, int neuron_size){
  int i;
  perceptron layer;

  for(i=0; i<how_many; i++){
    layer = perceptron(layer_size, neuron_size);
    _layers.push_back(layer);
    _connexions.push_back( synaptics() );
  }
}

void network::rmv_layers(int begin, int end){
  int num_of_layers, layer;

  layer = begin;
  num_of_layers = _layers.size();
  while(layer <= end && layer < num_of_layers){
    rmv_layer(layer);
    layer++;
  }
}

bool network::valid_unit(unit cell){
  int num_of_layers, theLayer_size;
  bool valid;

  valid = false;
  num_of_layers = _layers.size();
  if(0 <= cell.layer() && cell.layer() < num_of_layers){
    theLayer_size = _layers[cell.layer()].size();
    if(0 <= cell.pos() && cell.pos() < theLayer_size)
      return valid = true;
  }
  return valid;
}

bool network::registered_connection(synaptic synapse){
  int layer, size, i;
  bool found;
  
    found = false;
    if( valid_unit(synapse.source()) && valid_unit(synapse.dest()) ){
    layer = synapse.layer();
    size = _connexions[layer].size();
    _connexions[layer].set_cursor(0);
    i = 0;
    while(i<size && !found){
      if(_connexions[layer]() == synapse)
	found = true;
      else{
	i++;
	_connexions[layer]++;
      }
    }
  }
  return found;
}

bool network::registered_connection(unit src_unit, unit dst_unit){
  return registered_connection( synaptic(src_unit, dst_unit) );
}

bool network::registered_connection(int src_layer, int src_pos, int dst_layer, int dst_pos){
  return registered_connection( synaptic(src_layer, src_pos, dst_layer, dst_pos) );
}

int network::find_connection(synaptic synapse){
  int layer, i, pos, size;
  std::list<synaptic>::iterator it;
  bool found;
  
  found = false;
  if( valid_unit(synapse.source()) && valid_unit(synapse.dest()) ){
    layer = synapse.layer();
    i=0;
    _connexions[layer].set_cursor(0);
    size = _connexions[layer].size();
    while(i < size && !found){
      if(_connexions[layer]() == synapse)
	found = true;
      else{
	i++;
	_connexions[layer] ++;
      }
    }
  }
  pos = found ? i : -1;
  return pos;
}

int network::find_connection(unit src, unit dst){
  return find_connection( synaptic(src, dst) );
}

int network::find_connection(int src_layer, int src_pos, int dst_layer, int dst_pos){
  return find_connection( synaptic(src_layer, src_pos, dst_layer, dst_pos) );
}

bool network::are_connected(unit src, unit dst){
  return registered_connection( synaptic(src, dst) );
}

bool network::are_connected(int src_layer, int src_pos, int dst_layer, int dst_pos){
  return are_connected( unit(src_layer, src_pos), unit(dst_layer, dst_pos) );
}

void network::connect(unit src, unit dst){
  int layer;

  if( valid_unit(src) && valid_unit(dst) ){
    synaptic synapse(src, dst);
    if( !registered_connection(synapse) ){
      layer = synapse.layer();
      _connexions[layer] << synapse;
    }
  }
  else throw std::string("network::connect(unit,unit) : a given unit does not identify any cell of this network.");
}

void network::connect(int src_layer, int src_pos, int dst_layer, int dst_pos){
  connect( unit(src_layer, src_pos), unit(dst_layer, dst_pos) );
}

void network::disconnect(synaptic synapse){
  int layer, pos;

  pos = find_connection(synapse);
  if(pos >= 0){
    layer = synapse.layer();
    _connexions[layer].remove(pos);
  }
  else throw std::string("network::connect(synaptic) : given synapse argument not found in the network.");
}

void network::disconnect(unit src, unit dst){
  try{
    disconnect( synaptic(src, dst) );
  }
  catch(std::string){
    throw std::string("network::connect(unit,unit) : a given unit does not identify any cell of this network.");
  }
}

void network::disconnect(int src_layer, int src_pos, int dst_layer, int dst_pos){
  try{
    disconnect( synaptic(src_layer, src_pos, dst_layer, dst_pos) );
  }
  catch(std::string){
    throw std::string("network::connect(int,int,int,int) : a given couple does not identify any cell of this network.");
  }
}

void network::disconnect_incoming(unit cell){
  int layer, i, size;
  synaptic synapse;

  if( valid_unit(cell) ){
    layer = cell.layer();
    size = _connexions[layer].size();
    _connexions[layer].set_cursor(0);
    for(i=0; i<size; i++){
      synapse = _connexions[layer]();
      if( synapse.dest() == cell ){
	disconnect(synapse);
      }
      _connexions[layer]++;
    }
  }
  else throw std::string("network::disconnect_incoming(unit) : given unit does not identify any neuron of the network.");
}

void network::disconnect_incoming(int layer, int pos){
  try{
    disconnect_incoming( unit(layer, pos) );
  }
  catch(std::string){
    throw std::string("network::disconnect_incoming(int,int) : given couple does not identify any neuron of the network.");
  }
}

void network::disconnect_outgoing(unit cell, neurals::type net_type){
  int i, outgoing_layer, layer, num_of_layers, size;
  synaptic synapse;

  if( valid_unit(cell) ){
    outgoing_layer = cell.layer();

    //forward connections
    layer = outgoing_layer+1;
    num_of_layers = _layers.size();
    while(layer < num_of_layers){
      _connexions[layer].set_cursor(0);
      size = _connexions[layer].size();
      for(i=0; i<size; i++){
	synapse = _connexions[layer]();
	if( synapse.source() == cell ){
	  disconnect(synapse);
	}
	_connexions[layer]++;
      }      
      layer++;
    }

    //reccurent backward connections
    if(net_type == neurals::BACKWARD_ALLOWED){
      layer = outgoing_layer - 1;
      while(layer >= 0){
	size = _connexions[layer].size();
	_connexions[layer].set_cursor(0);
	for(i=0; i<size; i++){
	  synapse = _connexions[layer]();
	  if(synapse.source() == cell){
	    disconnect(synapse);
	  }
	  _connexions[layer]++;
	}      
	layer--;
      }
    }
  }
  else throw std::string("network::disconnect_outgoing(unit, neurals::type) : given unit does not identify any neuron of the network.");
}

void network::disconnect_outgoing(int layer, int pos, neurals::type net_type){
  try{
    disconnect_outgoing( unit(layer,pos), net_type );
  }
  catch(std::string){
    throw std::string("network::disconnect_outgoing(int,int, neurals::type) : given couple does not identify any neuron of the network.");
  }
}

void network::disconnect_all(unit cell, neurals::type net_type){
  try{
    disconnect_incoming(cell);
    disconnect_outgoing(cell, net_type);
  }
  catch(std::string e){
    throw std::string("network::disconnect_all(unit, neurals::type) : given unit does not identify any neuron of the network.");
  }
}

void network::disconnect_all(int layer, int pos, neurals::type net_type){
  try{
    disconnect_all( unit(layer,pos), net_type );
  }
  catch(std::string){
    throw std::string("network::disconnect_all(int,int, neurals::type) : given unit does not identify any neuron of the network.");
  }
}

void network::synaptic_injection(int layer){
  int num_of_layers, index, i, num_of_synapses;
  perceptron * dst_layer;
  perceptron * src_layer;
  neuron* dst_neuron;
  neuron* src_neuron;
  synaptic synapse;

  num_of_layers = _layers.size();
  if(0 <= layer && layer < num_of_layers){
    dst_layer = & _layers[layer];
    num_of_synapses = _connexions[layer].size();
    _connexions[layer].set_cursor(0);
    for(i=0; i<num_of_synapses; i++){
      synapse = _connexions[layer]();

      //incoming neuron
      index = synapse.dest().pos();
      dst_neuron = & (*dst_layer)[index];

      //outgoing neuron
      index = synapse.source().layer();
      src_layer = & _layers[index];
      index = synapse.source().pos();
      src_neuron = & (*src_layer)[index];

      //injection
      dst_neuron->receive( src_neuron->output() );

      _connexions[layer]++;
    }
  }
  else throw std::string("network::synaptic_injection(int) : invalid layer index.");
}

std::vector<unit> network::succ(unit src_unit, neurals::type net_type){
  int layer, num_of_layers, i, size;
  synaptic synapse;
  std::vector<unit> receivers;

  if( valid_unit(src_unit) ){
    //feed forward successors
    layer = src_unit.layer();
    num_of_layers = _layers.size();
    while(layer < num_of_layers){
      _connexions[layer].set_cursor(0);
      size = _connexions[layer].size();
      for(i=0; i<size; i++){
	synapse = _connexions[layer]();
	if(synapse.source() == src_unit){
	  receivers.push_back( synapse.dest() );
	}
	_connexions[layer]++;
      }
      layer ++;
    }

    //feed backward successors
    if(net_type == neurals::BACKWARD_ALLOWED){
      layer = src_unit.layer() - 1;
      num_of_layers = _layers.size();
      while(layer >= 0){
	size = _connexions[layer].size();
	_connexions[layer].set_cursor(0);
	for(i=0; i<size; i++){
	  synapse = _connexions[layer]();
	  if(synapse.source() == src_unit){
	    receivers.push_back( synapse.dest() );
	  }
	  _connexions[layer]++;
	}
	layer --;
      }
    }

    return receivers;
  }
  else throw std::string("network::succ(unit) : invalid given unit object.");
}

std::vector<unit> network::succ(int src_layer, int src_pos, neurals::type net_type){
  try{
    return succ( unit(src_layer, src_pos), net_type );
  }
  catch(std::string){
    throw std::string("network::succ(int,int) : invalid index given as parameter. No unit described.");
  }
}

std::vector<unit> network::pred(unit dst_unit){
  int layer, i, size;
  synaptic synapse;
  std::vector<unit> senders;

  if( valid_unit(dst_unit) ){
    //all incoming connections are in the layer of the dest_unit
    layer = dst_unit.layer();
    size = _connexions[layer].size();
    _connexions[layer].set_cursor(0);
    for(i=0; i<size; i++){
      synapse = _connexions[layer]();
      if(synapse.dest() == dst_unit){
	senders.push_back( synapse.source() );
      }
      _connexions[layer]++;
    }
    return senders;
  }
  else throw std::string("network::succ(unit) : invalid given unit object.");
}

std::vector<unit> network::pred(int dst_layer, int dst_pos){
  try{
    return pred( unit(dst_layer, dst_pos) );
  }
  catch(std::string){
    throw std::string("network::pred(int,int) : invalid passed argument. Invalid index.");
  }
}

void network::receive(double value){
  //input layer = layer 0
  _layers[0].receive(value);
}

void network::receive(std::vector<double> data){
  //input layer = layer 0
  _layers[0].receive(data);
}

void network::evaluate(){
  int i, num_of_layers;

  num_of_layers = _layers.size();
  if(num_of_layers > 0){
    //input layer evaluation
    _layers[0].evaluate();

    for(i=1; i < num_of_layers; i++){
      synaptic_injection(i);
      _layers[i].evaluate();
    }
  }
}

void network::evaluate(int num_of_times){
  int t;
  
  if(num_of_times > 0){
    t = 0;
    evaluate();
    
    for(t=t+1; t<num_of_times; t++){
      synaptic_injection();
      evaluate();
    }
  }
}

std::vector<float> network::output(){
  int last;

  //output layer = last layer
  last = _layers.size() - 1;
  return _layers[last].output();
}

void network::reset(){
  int i, num_of_layers;

  num_of_layers = _layers.size();
  for(i=0; i < num_of_layers; i++){
    _layers[i].reset();
  }
}

void network::print(){
  int i, size;

  size = _layers.size();
  std::cout<<"(((((((((("<<std::endl;
  for(i=0; i < size-1; i++){
    _layers[i].print();
    _connexions[i].print();
  }
  if(i == size-1){ 
    _layers[i].print();
    _connexions[i].print();
  }
  std::cout<<"))))))))))"<<std::endl;
}

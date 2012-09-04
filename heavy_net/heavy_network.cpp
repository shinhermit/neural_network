#include "heavy_network.hpp"

void heavy_network::_deep_layers_copy(const heavy_network & source){
  int i, size;

  size = source._layers.size();
  for(i=0; i<size; i++){
    _layers.push_back( new heavy_layer() );
    *_layers[i] = *source._layers[i];
  }
}

void heavy_network::_deep_layers_clear(){
  int i, size;

  size = _layers.size();
  for(i=0; i < size; i++){
    delete _layers[i];
  }
  _layers.clear();
}


heavy_network::heavy_network(){}

heavy_network::heavy_network(int layers_num, int neurons_per_layer, int inputs_per_neuron){
  int i;
  layer* p;

  for(i=0; i<layers_num; i++){
    p = new heavy_layer(neurons_per_layer, inputs_per_neuron);
    _layers.push_back(p);
  }
}

heavy_network::heavy_network(const heavy_network & source):_connexions(source._connexions){
  _deep_layers_copy(source);
}

heavy_network::~heavy_network(){
  _deep_layers_clear();  
  _connexions.clear();
}

heavy_network & heavy_network::operator=(const heavy_network & source){
  _deep_layers_clear();
  _deep_layers_copy(source);

  _connexions = source._connexions;

  return *this;
}

heavy_network & heavy_network::operator=(network & source){
  int i, size;

  _deep_layers_clear();

  size = source.size();
  for(i=0; i<size; i++){
    _layers.push_back( new heavy_layer() );
    *_layers[i] = *source[i];
  }

  _connexions = source.getConnections();

  return *this;
}

layer * heavy_network::operator[](int i){
  int num_of_layers;

  num_of_layers = _layers.size();
  if(0 <= i && i < num_of_layers){
    return _layers[i];
  }
  else{
    throw std::string("heavy_network::operator[](int): given layer number is out of range.");
  }
}

neuron * heavy_network::operator()(int layer, int pos){
  int num_of_layers, num_of_neurons;

  num_of_layers = _layers.size();
  if(0 <= layer && layer < num_of_layers){

    num_of_neurons = _layers[layer]->size();
    if(0 <= pos && pos < num_of_neurons){
      return _layers[layer]->operator[](pos);
    }
    else{
      throw std::string("heavy_network::operator()(int,int): given position is out of range.");
    }
  }
  else{
    throw std::string("heavy_network::operator()(int,int): given layer number is out of range.");
  }
}

heavy_network & heavy_network::operator>>(std::ostream & out){
  int i, size;

  size = _layers.size();
  out<<"----------"<<std::endl;
  for(i=0; i < size-1; i++){
    *_layers[i] >> out;
    out<<std::endl;
    if( _connexions.count(i) )
      _connexions[i] >> out;
    else
      out << "[]";
    out <<std::endl<<std::endl;
  }
  if(i == size-1){
    *_layers[i] >> out;
    out << std::endl;
    if( _connexions.count(i) )
      _connexions[i]>>out;
    else
      out << "[]";
    out<<std::endl;
  }
  out<<"----------"<<std::endl;
  return *this;
}

std::ostream & operator<<(std::ostream & out, heavy_network & net){
  net >> out;
  return out;
}


heavy_network & heavy_network::operator<<(layer* band){
  if(!band)
    band = new heavy_layer();

  _layers.push_back(band);

  return *this;
}

heavy_network & heavy_network::operator<<(double value){

  if( _layers.size() == 0 ){
    _layers.push_back( new heavy_layer() );
  }

  *_layers[0] << value;

  return *this;
}

heavy_network & heavy_network::operator<<(std::vector<double> & data){

  if( _layers.size() == 0 ){
    _layers.push_back( new heavy_layer() );
  }

  *_layers[0] << data;

  return *this;
}


int heavy_network::size()const{
  return _layers.size();
}

std::map<int,synaptics> heavy_network::getConnections(){
  return _connexions;
}

void heavy_network::add_neuron(int layer, neuron* cell){
  int num_of_layers;

  num_of_layers = _layers.size();
  if(0<=layer && layer<num_of_layers){

    if(!cell)
      cell = new heavy_neuron();

    _layers[layer]->add(cell);
  }
  else{
    throw std::string("heavy_network::add_neuron(int,neuron) : invalid layer index.");
  }
}

void heavy_network::rmv_neuron(int layer, int pos){
  int num_of_layers, num_of_neurons;

  num_of_layers = _layers.size();
  if(0<=layer && layer<num_of_layers){
    num_of_neurons = _layers[layer]->size();
    if(0<=pos && pos < num_of_neurons){
      disconnect_all(layer, pos);
      _layers[layer]->remove(pos);
    }
    else{
      throw std::string("heavy_network::rmv_neuron(int,int) : invalid neuron position.");
    }
  }
  else{
    throw std::string("heavy_network::rmv_neuron(int,int) : invalid layer index.");
  }
}

void heavy_network::add_layer(layer* band, int pos){

  if(!band)
    band = new heavy_layer();

  if( pos == -1 || abs(pos) >= _layers.size() ){
    _layers.push_back(band);
  }
  else{
    pos = abs(pos);
    _layers.insert(_layers.begin()+pos, band);
  }
}

void heavy_network::rmv_layer(int layer){
  int num_of_layers, size, pos;

  num_of_layers = _layers.size();
  if(0<=layer && layer < num_of_layers){
    size = _layers[layer]->size();
    for(pos=0; pos<size; pos++){
      disconnect_all(layer, pos);
    }
    delete _layers[layer];
    _layers.erase(_layers.begin()+layer);
  }
}

void heavy_network::add_layers(int how_many, int layer_size, int neuron_size){
  int i;
  layer* band;

  for(i=0; i<how_many; i++){
    band = new heavy_layer(layer_size, neuron_size);
    _layers.push_back(band);
  }
}

void heavy_network::rmv_layers(int begin, int end){
  int num_of_layers, layer;

  layer = begin;
  num_of_layers = _layers.size();
  while(layer <= end && layer < num_of_layers){
    rmv_layer(layer);
    end--;
    num_of_layers--;
  }
}

bool heavy_network::valid_cell(int xlayer, int ypos){
  int num_of_layers, num_of_neurons;
  bool valid;

  valid = false;
  num_of_layers = _layers.size();
  if(0 <= xlayer && xlayer < num_of_layers){
    num_of_neurons = _layers[xlayer]->size();
    if(0 <= ypos && ypos < num_of_neurons)
      return valid = true;
  }
  return valid;
}

int heavy_network::find_connection(int src_layer, int src_pos, int dst_layer, int dst_pos){
  int first, last, middle, pos;
  synaptic synapse;
  bool found;
  
  found = false;
  if( valid_cell(src_layer,src_pos) && valid_cell(dst_layer,dst_pos) ){

    if( _connexions.count(dst_layer) ){
      first = 0;
      last = _connexions[dst_layer].size() - 1;
      synapse = synaptic(src_layer,src_pos, dst_layer,dst_pos);
      while(first <= last && !found){
	middle = (first + last) / 2;
	if(_connexions[dst_layer][middle] == synapse){
	  found = true;
	}
	else if(_connexions[dst_layer][middle] < synapse){
	  first = middle+1;
	}
	else{
	  last = middle-1;
	}
      }
    }

  } //end if valid

  pos = found ? middle : -1;

  return pos;
}

bool heavy_network::has_connection(int src_layer, int src_pos, int dst_layer, int dst_pos){
  return ( find_connection(src_layer, src_pos, dst_layer, dst_pos) >= 0 );
}

void heavy_network::connect(int src_layer, int src_pos, int dst_layer, int dst_pos){
  int i, size;
  synaptic synapse;
  bool found;

  if( valid_cell(src_layer,src_pos) && valid_cell(dst_layer,dst_pos) ){
    synapse = synaptic(src_layer,src_pos, dst_layer,dst_pos);

    if( !_connexions.count(dst_layer) )
      _connexions.insert( std::pair<int,synaptics>(dst_layer, synaptics()) );
      
    size = _connexions[dst_layer].size();
    if(size == 0){
      _connexions[dst_layer] << synapse;
    }
    else{
      found = false;
      i=0;
      while(i < size && !found){
	if(_connexions[dst_layer][i] >= synapse)
	  found = true;
	else i++;
      }

      if(i < size){
	if(_connexions[dst_layer][i] != synapse)
	  _connexions[dst_layer].add(synapse, i);
      }
      else{
	_connexions[dst_layer] << synapse;
      }
    }

  }
  else{
    throw std::string("heavy_network::connect(int,int, int,int) : a given couple of coords does not identify any cell of this heavy_network.");
  }
}

void heavy_network::disconnect(int src_layer, int src_pos, int dst_layer, int dst_pos){
  int layer, pos;

  pos = find_connection(src_layer, src_pos, dst_layer, dst_pos);
  if(pos >= 0){
    layer = dst_layer;
    _connexions[layer].remove(pos);
  }
  else throw std::string("heavy_network::disconnect(int,int, int,int) : connection not found in the heavy_network.");
}

void heavy_network::disconnect_incoming(int layer, int pos){
  int i, size;
  unit cell(layer,pos);
  bool overpassed;

  if( valid_cell(layer,pos) ){
    if( _connexions.count(layer) ){
      size = _connexions[layer].size();
      overpassed = false;
      i=0;
      while(i < size && !overpassed){
	// the order of the 2 if() is important
	if(_connexions[layer][i].dest() > cell){
	  overpassed = true;
	}

	if(_connexions[layer][i].dest() == cell){
	  _connexions[layer].remove(pos);
	  i--;
	  size--;
	}

	i++;
      }
    }
  }
  else{
    throw std::string("heavy_network::disconnect_incoming(int,int) : given coords do not identify any neuron of the heavy_network.");
  }
}

void heavy_network::disconnect_outgoing(int layer, int pos){
  int i, j, num_of_layers, num_of_synapses;
  unit cell(layer,pos);

  if( valid_cell(layer,pos) ){
    num_of_layers = _layers.size();
    for(j=0; j < num_of_layers; j++){

      if( _connexions.count(j) ){

	num_of_synapses = _connexions[j].size();
	for(i=0; i < num_of_synapses; i++){

	  if( _connexions[j][i].source() == cell ){
	    _connexions[j].remove(i);
	    i--;
	    num_of_synapses--;
	  }
	}//fin for neurons
      }

    }//fin if valid()
  }
  else{
    throw std::string("heavy_network::disconnect_outgoing(int,int) : given coords does not identify any neuron of the heavy_network.");
  }
}

void heavy_network::disconnect_all(int layer, int pos){
  int i, j, num_of_layers, num_of_synapses;
  unit cell(layer,pos);

  if( valid_cell(layer,pos) ){
    num_of_layers = _layers.size();
    for(j=0; j < num_of_layers; j++){

      if( _connexions.count(j) ){

	num_of_synapses = _connexions[j].size();
	for(i=0; i < num_of_synapses; i++){

	  if( _connexions[j][i].source() == cell || _connexions[j][i].dest() == cell){
	    _connexions[j].remove(i);
	    i--;
	    num_of_synapses--;
	  }
	}//fin for neurons
      }

    }//fin if valid()
  }
  else{
    throw std::string("heavy_network::disconnect_all(int,int) : given coords do not identify any neuron of the heavy_network.");
  }
}

void heavy_network::synaptic_injection(int layer){
  int i, size, u,v, x,y;

  x = layer;
  size = _connexions[layer].size();
  for(i=0; i<size; i++ ){
    //outgoing neuron
    u = _connexions[layer][i].source().layer();
    v = _connexions[layer][i].source().pos();

    //incoming neuron
    y = _connexions[layer][i].dest().pos();

    //injection
    heavy_network & net = *this;
    *net(x,y) << net(u,v)->output();
  }
}

std::vector<unit> heavy_network::succ(int layer, int pos){
  int j, i, num_of_layers, num_of_synapses;
  std::vector<unit> receivers;
  unit cell(layer, pos);

  if( valid_cell(layer, pos) ){
    num_of_layers = _layers.size();
    for(j=0; j < num_of_layers; j++){

      if( _connexions.count(j) ){

	num_of_synapses = _connexions[j].size();
	for(i=0; i < num_of_synapses; i++){

	  if( _connexions[j][i].source() == cell ){
	    receivers.push_back( _connexions[j][i].dest() );
	  }
	}

      }
    }

    return receivers;
  }
  else{
    throw std::string("heavy_network::succ(int,int) : invalid neuron's coords.");
  }
}

std::vector<unit> heavy_network::pred(int layer, int pos){
  int j, i, num_of_layers, num_of_synapses;
  std::vector<unit> senders;
  unit cell(layer, pos);

  if( valid_cell(layer, pos) ){
    num_of_layers = _layers.size();
    for(j=0; j < num_of_layers; j++){

      if( _connexions.count(j) ){

	num_of_synapses = _connexions[j].size();
	for(i=0; i < num_of_synapses; i++){

	  if( _connexions[j][i].dest() == cell ){
	    senders.push_back( _connexions[j][i].source() );
	  }
	}

      }
    }

    return senders;
  }
  else{
    throw std::string("heavy_network::pred(int,int) : invalid neuron coordinates.");
  }
}

void heavy_network::receive(double value){
  if(_layers.size() == 0)
    _layers.push_back( new heavy_layer() );

  //input layer = layer 0
  _layers[0]->receive(value);
}

void heavy_network::receive(std::vector<double> data){
  if(_layers.size() == 0)
    _layers.push_back( new heavy_layer() );

  //input layer = layer 0
  _layers[0]->receive(data);
}

void heavy_network::evaluate(){
  int i, num_of_layers;

  num_of_layers = _layers.size();
  if(num_of_layers > 0){
    //input layer evaluation
    _layers[0]->evaluate();

    for(i=1; i < num_of_layers; i++){
      synaptic_injection(i);
      _layers[i]->evaluate();
    }
  }
}

void heavy_network::evaluate(int num_of_times){
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

std::vector<float> heavy_network::output(){
  int last;

  //output layer = last layer
  last = _layers.size() - 1;
  return _layers[last]->output();
}

void heavy_network::reset(){
  int i, num_of_layers;

  num_of_layers = _layers.size();
  for(i=0; i < num_of_layers; i++){
    _layers[i]->reset();
  }
}

void heavy_network::print(){
  int i, size;

  size = _layers.size();
  std::cout<<"(((((((((("<<std::endl;
  for(i=0; i < size-1; i++){
    _layers[i]->print();
    if( _connexions.count(i) )
      _connexions[i].print();
    else
      std::cout<<"()";
  }
  if(i == size-1){ 
    _layers[i]->print();
    if( _connexions.count(i) )
      _connexions[i].print();
    else
      std::cout<<"()";
  }
  std::cout<<"))))))))))"<<std::endl;
}

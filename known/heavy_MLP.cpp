#include "heavy_MLP.hpp"

void heavy_MLP::_deep_layers_copy(const heavy_MLP & source){
  int i, size;

  size = source._layers.size();
  for(i=0; i<size; i++){
    _layers.push_back( new heavy_layer() );
    *_layers[i] = *source._layers[i];
  }
}

void heavy_MLP::_deep_layers_clear(){
  int i, size;

  size = _layers.size();
  for(i=0; i < size; i++){
    delete _layers[i];
  }
  _layers.clear();
}


heavy_MLP::heavy_MLP(){}

heavy_MLP::heavy_MLP(int layers_num, int neurons_per_layer, int inputs_per_neuron){
  int i;
  layer* p;

  for(i=0; i<layers_num; i++){
    p = new heavy_layer(neurons_per_layer, inputs_per_neuron);
    _layers.push_back(p);
  }
}

heavy_MLP::heavy_MLP(const heavy_MLP & source){
  _deep_layers_copy(source);
}

heavy_MLP::~heavy_MLP(){
  _deep_layers_clear();  
}

heavy_MLP & heavy_MLP::operator=(const heavy_MLP & source){
  _deep_layers_clear();
  _deep_layers_copy(source);

  return *this;
}

heavy_MLP & heavy_MLP::operator=(network & source){
  int i, size;

  _deep_layers_clear();

  size = source.size();
  for(i=0; i<size; i++){
    _layers.push_back( new heavy_layer() );
    *_layers[i] = *source[i];
  }

  return *this;
}

layer * heavy_MLP::operator[](int i){
  int num_of_layers;

  num_of_layers = _layers.size();
  if(0 <= i && i < num_of_layers){
    return _layers[i];
  }
  else{
    throw std::string("heavy_MLP::operator[](int): given layer number is out of range.");
  }
}

neuron * heavy_MLP::operator()(int layer, int pos){
  int num_of_layers, num_of_neurons;

  num_of_layers = _layers.size();
  if(0 <= layer && layer < num_of_layers){

    num_of_neurons = _layers[layer]->size();
    if(0 <= pos && pos < num_of_neurons){
      return _layers[layer]->operator[](pos);
    }
    else{
      throw std::string("heavy_MLP::operator()(int,int): given position is out of range.");
    }
  }
  else{
    throw std::string("heavy_MLP::operator()(int,int): given layer number is out of range.");
  }
}

heavy_MLP & heavy_MLP::operator>>(std::ostream & out){
  int i, size;
  std::map<int,synaptics> connections = getConnections();

  size = _layers.size();
  out<<"----------"<<std::endl;
  for(i=0; i < size-1; i++){
    *_layers[i] >> out;
    out<<std::endl;
    if( connections.count(i) )
      connections[i] >> out;
    else
      out << "[]";
    out <<std::endl<<std::endl;
  }
  if(i == size-1){
    *_layers[i] >> out;
    if( connections.count(i) )
      connections[i]>>out;
    else
      out << "[]";
    out << std::endl;
  }
  out<<"----------"<<std::endl;
  return *this;
}

std::ostream & operator<<(std::ostream & out, heavy_MLP & net){
  net >> out;
  return out;
}


heavy_MLP & heavy_MLP::operator<<(layer* band){
  if(!band)
    band = new heavy_layer();

  _layers.push_back(band);

  return *this;
}

heavy_MLP & heavy_MLP::operator<<(double value){

  if( _layers.size() == 0 ){
    _layers.push_back( new heavy_layer() );
  }

  *_layers[0] << value;

  return *this;
}

heavy_MLP & heavy_MLP::operator<<(std::vector<double> & data){

  if( _layers.size() == 0 ){
    _layers.push_back( new heavy_layer() );
  }

  *_layers[0] << data;

  return *this;
}


int heavy_MLP::size()const{
  return _layers.size();
}

std::map<int,synaptics> heavy_MLP::getConnections(){
  int j, p, i, k, num_of_layers, num_of_neurons, num_of_preds;
  std::map<int,synaptics> connections;

  num_of_layers = _layers.size();
  for(j=1; j<num_of_layers; j++){
    p=j-1;
    num_of_preds = _layers[p]->size();
    if(num_of_preds > 0){
      connections.insert( std::pair<int,synaptics>(j, synaptics()) );
      num_of_neurons = _layers[j]->size();
      for(i=0; i<num_of_neurons; i++){
	for(k=0; k<num_of_preds; k++){
	  connections[j] << synaptic(p,k, j,i);
	}
      }
    }
  }
  return connections;
}

void heavy_MLP::add_neuron(int layer, neuron* cell){
  int num_of_layers;

  num_of_layers = _layers.size();
  if(0<=layer && layer<num_of_layers){

    if(!cell)
      cell = new heavy_neuron();

    _layers[layer]->add(cell);
  }
  else{
    throw std::string("heavy_MLP::add_neuron(int,neuron) : invalid layer index.");
  }
}

void heavy_MLP::rmv_neuron(int layer, int pos){
  int num_of_layers, num_of_neurons;

  num_of_layers = _layers.size();
  if(0<=layer && layer<num_of_layers){
    num_of_neurons = _layers[layer]->size();
    if(0<=pos && pos < num_of_neurons){
      disconnect_all(layer, pos);
      _layers[layer]->remove(pos);
    }
    else{
      throw std::string("heavy_MLP::rmv_neuron(int,int) : invalid neuron position.");
    }
  }
  else{
    throw std::string("heavy_MLP::rmv_neuron(int,int) : invalid layer index.");
  }
}

void heavy_MLP::add_layer(layer* band, int pos){

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

void heavy_MLP::rmv_layer(int layer){
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

void heavy_MLP::add_layers(int how_many, int layer_size, int neuron_size){
  int i;
  layer* band;

  for(i=0; i<how_many; i++){
    band = new heavy_layer(layer_size, neuron_size);
    _layers.push_back(band);
  }
}

void heavy_MLP::rmv_layers(int begin, int end){
  int num_of_layers, layer;

  layer = begin;
  num_of_layers = _layers.size();
  while(layer <= end && layer < num_of_layers){
    rmv_layer(layer);
    end--;
    num_of_layers--;
  }
}

bool heavy_MLP::valid_cell(int xlayer, int ypos){
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

int heavy_MLP::find_connection(int src_layer, int src_pos, int dst_layer, int dst_pos){
  int pos, num_of_preds;
  
  pos = -1;
  if( valid_cell(src_layer,src_pos) && valid_cell(dst_layer,dst_pos) ){
    num_of_preds = _layers[src_layer]->size();
    pos = dst_pos * num_of_preds + src_pos;
  }

  return pos;
}

bool heavy_MLP::has_connection(int src_layer, int src_pos, int dst_layer, int dst_pos){
  return ( find_connection(src_layer, src_pos, dst_layer, dst_pos) >= 0 );
}

void heavy_MLP::connect(int src_layer, int src_pos, int dst_layer, int dst_pos){
}

void heavy_MLP::disconnect(int src_layer, int src_pos, int dst_layer, int dst_pos){
}

void heavy_MLP::disconnect_incoming(int layer, int pos){
}

void heavy_MLP::disconnect_outgoing(int layer, int pos){
}

void heavy_MLP::disconnect_all(int layer, int pos){
}

void heavy_MLP::synaptic_injection(int j){
  int p, i,k, num_of_preds, num_of_neurons, num_of_layers;

  num_of_layers = _layers.size();
  if(0<j && j <num_of_layers){

    p = j-1;
    num_of_preds = _layers[p]->size();
    if(num_of_preds > 0){

      num_of_neurons = _layers[j]->size();
      for(i=0; i<num_of_neurons; i++){
	for(k=0; k<num_of_preds; k++){
	  //injection
	  heavy_MLP & net = *this;
	  *net(j,i) << net(p,k)->output();	  
	}
      }

    }

  }
}

std::vector<unit> heavy_MLP::succ(int j, int i){
  int last, p, k, num_of_succs;
  std::vector<unit> receivers;

  if( valid_cell(j, i) ){

    last = _layers.size()-1;
    if(j != last){
      p=j+1;
      num_of_succs = _layers[p]->size();
      for(k=0; k<num_of_succs; k++){
	receivers.push_back( unit(p,k) );
      }
    }

    return receivers;
  }
  else{
    throw std::string("heavy_MLP::succ(int,int) : invalid neuron's coords.");
  }
}

std::vector<unit> heavy_MLP::pred(int j, int i){
  int p, k, num_of_preds;
  std::vector<unit> senders;

  if( valid_cell(j, i) ){

    if(j != 0){
      p=j-1;
      num_of_preds = _layers[p]->size();
      for(k=0; k<num_of_preds; k++){
	senders.push_back( unit(p,k) );
      }
    }

    return senders;
  }
  else{
    throw std::string("heavy_MLP::pred(int,int) : invalid neuron coordinates.");
  }
}

void heavy_MLP::receive(double value){
  if(_layers.size() == 0)
    _layers.push_back( new heavy_layer() );

  //input layer = layer 0
  _layers[0]->receive(value);
}

void heavy_MLP::receive(std::vector<double> data){
  if(_layers.size() == 0)
    _layers.push_back( new heavy_layer() );

  //input layer = layer 0
  _layers[0]->receive(data);
}

void heavy_MLP::evaluate(){
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

void heavy_MLP::evaluate(int num_of_times){
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

std::vector<float> heavy_MLP::output(){
  int last;

  //output layer = last layer
  last = _layers.size() - 1;
  return _layers[last]->output();
}

void heavy_MLP::reset(){
  int i, num_of_layers;

  num_of_layers = _layers.size();
  for(i=0; i < num_of_layers; i++){
    _layers[i]->reset();
  }
}

void heavy_MLP::clear_connections(){
}

void heavy_MLP::clear(){
  _deep_layers_clear();
}

void heavy_MLP::save(std::ostream&){
  
}

void heavy_MLP::load(std::istream&){
  
}

void heavy_MLP::print(){
  int i, size;

  size = _layers.size();
  std::cout<<"(((((((((("<<std::endl;
  for(i=0; i < size; i++){
    _layers[i]->print();
  }
  std::cout<<"))))))))))"<<std::endl;
}

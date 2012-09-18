#include "heavy_layer.hpp"

void heavy_layer::_deep_copy(const heavy_layer & source){
  int i, size;

  size = source.size();
  for(i=0; i<size; i++){
    _neurons.push_back( new heavy_neuron() );
    *_neurons[i] = * source._neurons[i];
  }
}

void heavy_layer::_deep_clear(){
  int i;

  for(i=0; i<(int)_neurons.size(); i++){
    delete _neurons[i];
    _neurons[i] = NULL;
  }
  _neurons.clear();
}

heavy_layer::heavy_layer(){}

heavy_layer::heavy_layer(int size, int neuron_size){
  int i;

  for(i=0; i<size; i++){
    _neurons.push_back( new heavy_neuron(neuron_size) );
  }
}

heavy_layer::heavy_layer(const heavy_layer & source){
  _deep_copy(source);
}

heavy_layer::~heavy_layer(){
  _deep_clear();
}

heavy_layer & heavy_layer::operator=(const heavy_layer & source){

  _deep_clear();
  _deep_copy(source);

  return *this;
}

heavy_layer & heavy_layer::operator=(layer & source){
  int i, size;

  _deep_clear();

  size = source.size();
  for(i=0; i<size; i++){
    _neurons.push_back( new heavy_neuron() );
    *_neurons[i] = *source[i];
  }

  return *this;
}

neuron * heavy_layer::operator[](int pos){
  int size;

  size = _neurons.size();

  if(0 <= pos && pos < size)
    return _neurons[pos];
  else
    throw std::string("heavy_layer::operator[](int) : out of range index for neuron access.");
}

heavy_layer & heavy_layer::operator>>(std::ostream & out){
  int i;

  out<<"[";

  for(i=0; i<(int)_neurons.size(); i++){
    *_neurons[i] >> out;
  }

  out<<"]";

  return *this;
}

std::ostream & operator<<(std::ostream & out, heavy_layer & layer){
  layer >> out;
  return out;  
}

heavy_layer & heavy_layer::operator<<(double value){
  int i;

 for(i=0; i<(int)_neurons.size(); i++){
    if( _neurons[i]->input_index() <= _neurons[i]->size() )
      *_neurons[i] << value;
  }

  return *this;
}

heavy_layer & heavy_layer::operator<<(const std::vector<double> & data){
  int i;

  for(i=0; i<(int)data.size(); i++){
    operator<<(data[i]); //calling heavy_layer::operator<<(double)
  }

  return *this;
}

heavy_layer & heavy_layer::operator<<(neuron* cell){
  if(cell)
    _neurons.push_back(cell);

  return *this;
}

int heavy_layer::size()const{return _neurons.size();}

void heavy_layer::resize(int newsize){
  int i, oldsize, ref_size;

  if(newsize>=0){
    oldsize = _neurons.size();

    if(oldsize > 0)
      ref_size = _neurons[0]->size();

    //if elements will removed
    for(i=oldsize-1; i>=newsize; i--){
      delete _neurons[i];
    }

    _neurons.resize(newsize);

    //if elements have been added
    for(i=oldsize+1; i<newsize; i++){
      _neurons[i] = new heavy_neuron(ref_size);
    }
  }
  else{
    throw std::string("heavy_layer::size() : invalid negative value for heavy_layer's size");
  }
}

void heavy_layer::add(neuron* cell, int pos){

  if( pos == -1 || abs(pos) > (int)_neurons.size() ){
    _neurons.push_back(cell);
  }
  else{
    _neurons.insert( _neurons.begin()+abs(pos), cell );
  }
}

void heavy_layer::remove(int pos){

  if( 0<=pos && pos < (int)_neurons.size() ){
    delete _neurons[pos];
    _neurons.erase(_neurons.begin()+pos);
  }
  else{
    throw std::string("heavy_layer::remove(int) : out of range value for neuron's position");
  }
}

void heavy_layer::rnd_weights(double min, double max){
  int i;

  for(i=0; i < (int)_neurons.size(); i++){
    _neurons[i]->rnd_weights(min,max);
  } 
}

void heavy_layer::receive(double value){
  int i, size;

  size = _neurons.size();
  for(i=0; i < size; i++){
    if( _neurons[i]->input_index() <= _neurons[i]->size() )
      _neurons[i]->receive(value);
  }
}

void heavy_layer::receive(std::vector<double> data){
  int i, size;

  size = data.size();
  for(i=0; i < size; i++){
    receive(data[i]);
  }
}

void heavy_layer::evaluate(){
  int i, size;

  size = _neurons.size();
  for(i=0; i<size; i++){
    _neurons[i]->evaluate();
  }
}

std::vector<float> heavy_layer::output(){
  std::vector<float> outputs;
  int i, size;

  size = _neurons.size();
  for(i=0; i<size; i++){
    outputs.push_back( _neurons[i]->output() );
  }
  return outputs;
}

void heavy_layer::reset(){
  int i, size;

  size = _neurons.size();
  for(i=0; i<size; i++){
    _neurons[i]->reset();
  }
}

void heavy_layer::save(std::ostream & ofile){
  int i, size;

  ofile << "[" << std::endl;

  size = _neurons.size();
  for(i=0; i < size; i++){
    _neurons[i]->save(ofile);
    ofile << std::endl;
  }

  ofile << "]";
}

void heavy_layer::load(std::istream & ifile){
  std::string line, begin_layer, end_layer;
  std::istringstream iss;
  bool layer_closed;
  neuron * cell;

  begin_layer = "[";
  end_layer = "]";

  while( ifile.good() && line != begin_layer ){
    std::getline(ifile, line);
  }

  if( ifile.good() ){
    _deep_clear();
  }

  layer_closed = false;
  while( ifile.good() && !layer_closed ){

    std::getline(ifile, line);

    try{

      if(line == end_layer){
	layer_closed = true;
      }
      else{
	cell = new heavy_neuron();
	iss.clear();
	iss.str(line);
	cell->load(iss);
	_neurons.push_back(cell);
      }

    }
    catch(std::string e){
      delete cell;
      throw std::string("exception! heavy_layer::load(std::istream&) : cell->load(iss) failed\n")+e;
    }

  }//end while !layer_closed
}

void heavy_layer::print(){
  int i, size;

  std::cout<<"("<<std::endl;
  size = _neurons.size();
  for(i=0; i<size; i++){
    _neurons[i]->print();
  }
  std::cout<<")"<<std::endl;
}

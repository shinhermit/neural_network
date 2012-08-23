#include "neuron.hpp"

float neuron::_activation(double buffered){
  return 1/(1 + exp(-1*buffered));
}

neuron::neuron(int nbr_of_inputs): _size( abs(nbr_of_inputs) ), _weights( std::vector<double>( abs(nbr_of_inputs+1) ) ), _index(0), _buffer(0), _output(neurals::UNEVALUATED){
  rnd_weights();
}

neuron::neuron(const neuron & source):_size(source._size), _weights(source._weights), _index(source._index), _buffer(source._buffer), _output(source._output){}

neuron::~neuron(){}

neuron & neuron::operator=(const neuron & source){
  _buffer = source._buffer;
  _output = source._output;
  _weights.clear();
  _weights = source._weights;
  _size = source._size;
  _index = source._index;
  return *this;
}

neuron & neuron::operator>>(std::ostream & out){
  int i;

  out<<"("<<_size<< ", [";

  for(i=0; i < _size; i++)
    out<<_weights[i]<<"|";
  if(i <= _size)
    out<<_weights[i];

  out<<"], "<<_index<<", "<<_buffer<<", "<<_output<<")";

  return *this;
}

std::ostream & operator<<(std::ostream & out, neuron & cell){
  cell >> out;
  return out;
}

neuron & neuron::operator<<(double value){
  if(_index+1 <= _size){
    _index++;
    _buffer += _weights[_index] * value;
  }
  return *this;
}

neuron & neuron::operator<<(const std::vector<double> & data){
  int i;
  int data_size = data.size();

  for(i=0; i < data_size && _index < _size; i++){
    operator<<(data[i]); //appel de neuron::operator(double)
  }
  return *this;
}

void neuron::rnd_weights(double min, double max){
  int i;

  srand(time(NULL));
  for(i=0; i<=_size; i++){
    _weights[i] = ( rand()/(double)RAND_MAX ) * (max-min) + min;
  }
}

void neuron::receive(double value){
  if(_index+1 <= _size){
    _index++;
    _buffer += _weights[_index] * value;
  }
  else throw std::string("neuron::receive(double) : input index extends unit size");
}

void neuron::receive(const std::vector<double> & data){
  int i;
  int data_size = data.size();

  try{
    for(i=0; i < data_size && _index < _size; i++){
      receive(data[i]);
    }
  }
  catch(std::string){
    throw std::string("neuron::receive(std::vector<double>&) : input index extends unit size");
  }
}

float neuron::evaluate(){
  _buffer -= _weights[0]; // prise en compte du coefficient de biais

  _output = _activation(_buffer);
  _index = 0;
  _buffer = 0;
  return _output;
}

bool neuron::is_active()const{return _output >= neurals::THRESHOLD;}

int neuron::input_index()const{return _index;}

int neuron::size()const{return _size;}

void neuron::reset(){
  _buffer = 0;
  _output = neurals::UNEVALUATED;
  _index = 0;
}

void neuron::resize(int size, double minWeight, double maxWeight){
  int oldsize, i;
  oldsize = _size;

  if(size >= 0){
    _size = size;

    if(_index > _size)
      _index = _size;

    _weights.resize(_size+1);
    if(_size > oldsize){
      srand(time(NULL));
      for(i=oldsize+1; i<=_size; i++){
	_weights[i] = ( rand()/(double)RAND_MAX ) * (maxWeight-minWeight) + minWeight;
      }
    }

  }
}

float neuron::output()const{return _output;}

short neuron::binary_output()const{
  short bin;

  bin = (_output >= neurals::THRESHOLD) ? 1 : 0;
  return bin;
}

double neuron::getWeight(int i){
  if(0 <= i && i <= _size)
    return _weights[i];
  else throw std::string("neuron::output() : weight index extends unit size");
}

void neuron::setWeight(int i, double value){
  if(0 <= i && i <= _size)
    _weights[i] = value;
  else throw std::string("neuron::setWeight(int, double) : weight index extends unit size");
}

void neuron::print(){
  int i;

  std::cout<<"(size:"<<_size<< ", weights: [";

  for(i=0; i < _size; i++)
    std::cout<<_weights[i]<<"|";
  if(i <= _size)
    std::cout<<_weights[i];

  std::cout<<"], input index:"<<_index<<", buffer:"<<_buffer<<", output:"<<_output<<")"<<std::endl;
}

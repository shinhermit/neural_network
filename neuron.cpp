#include "neuron.hpp"

float neuron::_activation(double buffered){
  return 1/(1 + exp(-1*buffered));
}

neuron::neuron(int nbr_of_inputs):_buffer(0), _output(-1), _weights( std::vector<double>( abs(nbr_of_inputs) ) ), _size( abs(nbr_of_inputs) ), _index(0){
  rnd_weights();
}

neuron::neuron(const neuron & source):_buffer(source._buffer), _output(source._output), _weights(source._weights), _size(source._size), _index(source._index){}

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

void neuron::rnd_weights(double min, double max){
  int i;

  srand(time(NULL));
  for(i=0; i<=_size; i++){
    _weights[i] = ( rand()/(double)RAND_MAX ) * (max-min) + min;
  }
}

void neuron::receive(double value){
  _index++;
  if(_index <= _size){
    _buffer += _weights[_index] * value;
  }
  else throw "neuron::receive(double) : input index extends unit size";
}

void neuron::receive(std::vector<double> & data){
  int i;
  int data_size = data.size();

  try{
    for(i=0; i < data_size && i < _size; i++){
      receive(data[i]);
    }
  }
  catch(std::string){
    throw "neuron::receive(std::vector<double>&) : input index extends unit size";
  }
}

float neuron::evaluate(){
  _buffer -= _weights[0]; // prise en compte du coefficient de biais

  _output = _activation(_buffer);
  _index = 0;
  _buffer = 0;
  return _output;
}

int neuron::input_index()const{return _index;}

int neuron::size()const{return _size;}

void neuron::reset(){
  _buffer = 0;
  _output = -1;
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

double neuron::getWeight(int i){
  if(0 <= i && i <= _size)
    return _weights[i];
  else throw "neuron::output() : weight index extends unit size";
}

void neuron::setWeight(int i, double value){
  if(0 <= i && i <= _size)
    _weights[i] = value;
  else throw "neuron::setWeight(int, double) : weight index extends unit size";
}

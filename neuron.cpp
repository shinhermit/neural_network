#include "neuron.hpp"

float neuron::_activation(double buffered){
  return 1/(1 + exp(-1*buffered));
}

neuron::neuron(int nbr_of_inputs):_buffer(0), _ouput(-1), _weights(vector<double>(nbr_of_inputs)), _size(nbr_of_inputs), _index(0){
  rnd_weights();
}

neuron::neuron(const neuron & source):_buffer(source._buffer), _ouput(source._output), _weights(source._weights), _size(source._size), _index(source._index){}

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
  for(i=0; i<=size; i++){
    _weights[i] = ( rand()/(double)RAND_MAX ) * (max-min) + min;
  }
}

void neuron::receive(double value){
  _index++;
  if(_index <= _size){
    _buffer += weights[_index] * value;
  }
  else throw "input index extends unit size";
}

void neuron::receive(vector<double> & data){
  int i;
  for(i=0; i < data.size() && i < _size; i++){
    _receive(data[i]);
  }
}

float neuron::evaluate(){
  _buffer -= _weights[0]; // prise en compte du coefficient de biais

  _output = _activation(_buffer);
  _index = 0;
  _buffer = 0;
  return _output;
}

void neuron::reset(){
  _buffer = 0;
  _output = -1;
  _index = 0;
}

void neuron::resize(int size, double minWeight, double maxWeight){
  int oldsize, i;

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
  else throw "weight index extends unit size";
}

void neuron::setWeight(int i, double value){
  if(0 <= i && i <= _size)
    _weights[i] = value;
  else throw "weight index extends unit size";
}

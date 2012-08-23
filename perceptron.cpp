#include "perceptron.hpp"

perceptron::perceptron(){}

perceptron::perceptron(int size, int neuron_size){
  int i;

  for(i=0; i<size; i++){
    _neurons.push_back( neuron(neuron_size) );
  }
}

perceptron::perceptron(const perceptron & source):_neurons(source._neurons){}

perceptron::~perceptron(){}

perceptron & perceptron::operator=(const perceptron & source){
  _neurons.clear();
  _neurons = source._neurons;
  return *this;
}

neuron & perceptron::operator[](int pos){
  int size;

  size = _neurons.size();
  if(0 <= pos && pos < size)
    return _neurons[pos];
  else throw std::string("perceptron::operator[](int) : out of range index for neuron access.");
}

perceptron & perceptron::operator>>(std::ostream & out){
  int i, size;

  out<<"[";
  size = _neurons.size();
  for(i=0; i<size; i++){
    out<<_neurons[i];
  }
  out<<"]";

  return *this;
}

std::ostream & operator<<(std::ostream & out, perceptron & perceptor){
  perceptor >> out;
  return out;  
}

perceptron & perceptron::operator<<(double value){
  int i, size;

  size = _neurons.size();
  for(i=0; i<size; i++){
    if( _neurons[i].input_index() <= _neurons[i].size() )
      _neurons[i]<<value;
  }
  return *this;
}

perceptron & perceptron::operator<<(const std::vector<double> & data){
  int i, size;

  size = data.size();
  for(i=0; i<size; i++){
    operator<<(data[i]); //calling perceptron::operator<<(double)
  }
  return *this;
}

perceptron & perceptron::operator<<(neuron cell){
  _neurons.push_back(cell);
  return *this;
}

int perceptron::size()const{return _neurons.size();}

void perceptron::resize(int newsize){
  if(newsize>0){
    _neurons.resize(newsize);
  }
  else throw std::string("perceptron::size() : invalid negative value for perceptron's size");
}

void perceptron::add(neuron cell, int pos){
  int size = _neurons.size();

  if(pos == -1 || abs(pos) >size){
    _neurons.push_back(cell);
  }
  else{
    _neurons.insert( _neurons.begin()+abs(pos), cell );
  }
}

void perceptron::remove(int pos){
  int size;

  size = _neurons.size();
  if(0<=pos && pos<size){
    _neurons.erase(_neurons.begin()+pos);
  }
  else throw std::string("perceptron::remove(int) : out of range value for neuron's position");
}

void perceptron::rnd_weights(double min, double max){
  int i, size;

  size = _neurons.size();
  for(i=0; i<size; i++){
    _neurons[i].rnd_weights(min,max);
  } 
}

void perceptron::receive(double value){
  int i, size;

  size = _neurons.size();
  for(i=0; i<size; i++){
    if( _neurons[i].input_index() <= _neurons[i].size() )
      _neurons[i].receive(value);
  }
}

void perceptron::receive(std::vector<double> data){
  int i, size;

  size = data.size();
  for(i=0; i<size; i++){
    receive(data[i]);
  }
}

void perceptron::evaluate(){
  int i, size;

  size = _neurons.size();
  for(i=0; i<size; i++){
    _neurons[i].evaluate();
  }
}

std::vector<float> perceptron::output(){
  std::vector<float> outputs;
  int i, size;

  size = _neurons.size();
  for(i=0; i<size; i++){
    outputs.push_back( _neurons[i].output() );
  }
  return outputs;
}

void perceptron::reset(){
  int i, size;

  size = _neurons.size();
  for(i=0; i<size; i++){
    _neurons[i].reset();
  }
}

void perceptron::print(){
  int i, size;

  std::cout<<"("<<std::endl;
  size = _neurons.size();
  for(i=0; i<size; i++){
    _neurons[i].print();
  }
  std::cout<<")"<<std::endl;
}

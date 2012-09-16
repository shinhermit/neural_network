#include "heavy_neuron.hpp"

bool heavy_neuron::_seeded = false;

bool heavy_neuron::seeded(){return heavy_neuron::_seeded;}

heavy_neuron::heavy_neuron(int nbr_of_inputs): _size( abs(nbr_of_inputs) ), _weights( std::vector<double>( abs(nbr_of_inputs+1) ) ), _index(0), _buffer(0), _output(neurals::UNEVALUATED){
  rnd_weights();
}

heavy_neuron::heavy_neuron(const heavy_neuron & source):_size(source._size), _weights(source._weights), _index(source._index), _buffer(source._buffer), _output(source._output){}

heavy_neuron::~heavy_neuron(){}

heavy_neuron & heavy_neuron::operator=(const heavy_neuron & source){
  _buffer = source._buffer;
  _output = source._output;
  _weights.clear();
  _weights = source._weights;
  _size = source._size;
  _index = source._index;
  return *this;
}

heavy_neuron & heavy_neuron::operator=(neuron & source){
  _buffer = source.getBuffer();
  _output = source.output();
  _weights.clear();
  _weights = source.weights();
  _size = source.size();
  _index = source.input_index();
  return *this;
}

heavy_neuron & heavy_neuron::operator>>(std::ostream & out){
  int i;

  out<<"("<<_size<< ", [";

  for(i=0; i < _size; i++)
    out<<_weights[i]<<"|";
  if(i <= _size)
    out<<_weights[i];

  out<<"], "<<_index<<", "<<_buffer<<", "<<_output<<")";

  return *this;
}

std::ostream & operator<<(std::ostream & out, heavy_neuron & cell){
  cell >> out;
  return out;
}

heavy_neuron & heavy_neuron::operator<<(double value){
  if(_index+1 <= _size){
    _index++;
    _buffer += _weights[_index] * value;
  }
  return *this;
}

heavy_neuron & heavy_neuron::operator<<(const std::vector<double> & data){
  int i;
  int data_size = data.size();

  for(i=0; i < data_size && _index < _size; i++){
    operator<<(data[i]); //appel de heavy_neuron::operator(double)
  }
  return *this;
}

void heavy_neuron::rnd_weights(double min, double max){
  int i;

  if(!_seeded){
    srand(time(NULL));
    _seeded = true;
  }

  for(i=0; i<=_size; i++){
    _weights[i] = ( rand()/(double)RAND_MAX ) * (max-min) + min;
  }
}

void heavy_neuron::receive(double value){
  if(_index+1 <= _size){
    _index++;
    _buffer += _weights[_index] * value;
  }
  else throw std::string("heavy_neuron::receive(double) : input index extends unit size");
}

void heavy_neuron::receive(const std::vector<double> & data){
  int i;
  int data_size = data.size();

  try{
    for(i=0; i < data_size && _index < _size; i++){
      receive(data[i]);
    }
  }
  catch(std::string){
    throw std::string("heavy_neuron::receive(std::vector<double>&) : input index extends unit size");
  }
}

float heavy_neuron::evaluate(){
  _buffer -= _weights[0]; // prise en compte du coefficient de biais

  _output = _activation(_buffer);
  _index = 0;
  _buffer = 0;
  return _output;
}

bool heavy_neuron::is_active()const{return _output >= neurals::THRESHOLD;}

int heavy_neuron::input_index()const{return _index;}

int heavy_neuron::size()const{return _size;}

void heavy_neuron::reset(){
  _buffer = 0;
  _output = neurals::UNEVALUATED;
  _index = 0;
}

void heavy_neuron::resize(int size, double minWeight, double maxWeight){
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

double heavy_neuron::getBuffer()const{return _buffer;}

float heavy_neuron::output()const{return _output;}

short heavy_neuron::binary_output()const{
  short bin;

  bin = (_output >= neurals::THRESHOLD) ? neurals::BINARY_HIGH : neurals::BINARY_LOW;

  return bin;
}

double heavy_neuron::getWeight(int i){
  if(0 <= i && i <= _size)
    return _weights[i];
  else throw std::string("heavy_neuron::output() : weight index extends unit size");
}

std::vector<double> heavy_neuron::weights(){
  return _weights;
}

void heavy_neuron::setWeight(int i, double value){
  if(0 <= i && i <= _size)
    _weights[i] = value;
  else throw std::string("heavy_neuron::setWeight(int, double) : weight index extends unit size");
}

void heavy_neuron::save(std::ostream & ofile){
  int i;

  ofile<<_size<<" ";

  for(i=0; i <= _size; i++)
    ofile<<_weights[i]<<" ";

  ofile<<_index<<" "<<_buffer<<" "<<_output;
}

void heavy_neuron::load(std::istream & ifile){
  std::string line;
  int i, size;

  size = 0;

  if( ifile.good() ){
    
    ifile >> size;

    if(size > _size) _weights.resize(size+1);

    if(size > 0) _size = size;

    i=0;
    while( ifile.good() && i<=_size ){
      ifile >> _weights[i];
      i++;
    }

    if( ifile.good() )
      ifile >> _index;

    if( !ifile.good() )
      ifile >> _buffer;

    if( !ifile.good() )
      ifile >> _output;
  }

}

void heavy_neuron::print(){
  int i;

  std::cout<<"(size:"<<_size<< ", weights: [";

  for(i=0; i < _size; i++)
    std::cout<<_weights[i]<<"|";
  if(i <= _size)
    std::cout<<_weights[i];

  std::cout<<"], input index:"<<_index<<", buffer:"<<_buffer<<", output:"<<_output<<")"<<std::endl;
}

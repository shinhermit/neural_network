#include "h_pattern.hpp"

h_pattern::h_pattern(){}

h_pattern::h_pattern(const h_pattern & source):pattern(source){}

h_pattern::~h_pattern(){}

h_pattern & h_pattern::operator=(const h_pattern & source){
  pattern::operator=(source);

  return *this;
}

h_pattern & h_pattern::operator=(const pattern & source){
  pattern::operator=(source);

  return *this;
}

h_pattern & h_pattern::operator>>(std::ostream & out){
  int i, size;

  out<<"........."<<std::endl;
  out<<"i[";

  size = _inputs.size();
  for(i=0; i<size-1; i++){
    out<<_inputs[i]<<", ";
  }
  if(i < size){
    out<<_inputs[i];
  }

  out<<"]"<<std::endl;

  out<<"o[";

  size = _outputs.size();
  for(i=0; i<size-1; i++){
    out<<_outputs[i]<<", ";
  }
  if(i < size){
    out<<_outputs[i];
  }

  out<<"]"<<std::endl;

  out<<"........."<<std::endl;

  return *this;
}

std::ostream & operator<<(std::ostream & out, h_pattern & example){
  example >> out;
  return out;
}

h_pattern & h_pattern::operator<<(double value){
  _inputs.push_back(value);
  return *this;
}

h_pattern & h_pattern::operator()(float value){
  _outputs.push_back(value);
  return *this;
}

int h_pattern::inputs_size(){
  return _inputs.size();
}

int h_pattern::outputs_size(){
  return _outputs.size();
}

h_pattern & h_pattern::receive_input(double value){
  _inputs.push_back(value);
  return *this;
}

h_pattern & h_pattern::receive_ouput(float value){
  _outputs.push_back(value);
  return *this;
}

h_pattern & h_pattern::receive_input(std::vector<double> data){
  _inputs = data;
  return *this;
}

h_pattern & h_pattern::receive_ouput(std::vector<float> data){
  _outputs = data;
  return *this;
}

h_pattern & h_pattern::receive_input(std::istream & in){
  std::cout<<"calling abstract method h_pattern::receive_input(std::istream&)"<<std::endl;
  return *this;
}

h_pattern & h_pattern::receive_ouput(std::istream & in){
  std::cout<<"calling abstract method h_pattern::receive_ouput(std::istream&)"<<std::endl;
  return *this;
}

double h_pattern::input(int pos){
  if( 0<=pos && pos<(int)_inputs.size() ){
    return _inputs[pos];
  }
  else{
    throw std::string("exception! h_pattern::input(int) : given indice is out of range.");
  }
}

float h_pattern::output(int pos){
  if( 0<=pos && pos<(int)_outputs.size() ){
    return _outputs[pos];
  }
  else{
    throw std::string("exception! h_pattern::output(int) : given indice is out of range.");
  }
}

std::vector<double> & h_pattern::inputs(){
  return _inputs;
}

std::vector<float> & h_pattern::outputs(){
  return _outputs;
}

void h_pattern::print(){
  int i, size;

  std::cout<<"........."<<std::endl;
  std::cout<<"Inputs: [";
  size = _inputs.size();
  for(i=0; i<size-1; i++){
    std::cout<<_inputs[i]<<", ";
  }
  if(i < size){
    std::cout<<_inputs[i]<<"]"<<std::endl;
  }

  std::cout<<"Outputs: [";
  size = _outputs.size();
  for(i=0; i<size-1; i++){
    std::cout<<_outputs[i]<<", ";
  }
  if(i < size){
    std::cout<<_outputs[i]<<"]"<<std::endl;
  }
  std::cout<<"........."<<std::endl;
}

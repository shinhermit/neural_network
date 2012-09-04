#include "pattern.hpp"

pattern::pattern(){}

pattern::pattern(const pattern & source):_inputs(source._inputs), _outputs(source._outputs){}

pattern::~pattern(){}

pattern & pattern::operator=(const pattern & source){
  _inputs = source._inputs;
  _outputs = source._outputs;

  return *this;
}

pattern & pattern::operator>>(std::ostream & out){
  std::cout<<"calling abstract method pattern::operator>>(std::ostream&)"<<std::endl;
  return *this;
}

std::ostream & operator<<(std::ostream & out, pattern * example){
  *example >> out;
  return out;
}

pattern & pattern::operator<<(double value){
  std::cout<<"calling abstract method pattern::operator<<(double)"<<std::endl;
  return *this;
}

pattern & pattern::operator()(float value){
  std::cout<<"calling abstract method pattern::operator()(float)"<<std::endl;
  return *this;
}

int pattern::inputs_size(){
  std::cout<<"calling abstract method pattern::inputs_size()"<<std::endl;
  return -1;
}

int pattern::outputs_size(){
  std::cout<<"calling abstract method pattern::outputs_size()"<<std::endl;
  return -1;
}

pattern & pattern::receive_input(double value){
  std::cout<<"calling abstract method pattern::receive_input(double)"<<std::endl;
  return *this;
}

pattern & pattern::receive_ouput(float value){
  std::cout<<"calling abstract method pattern::receive_ouput(float)"<<std::endl;
  return *this;
}

pattern & pattern::receive_input(std::vector<double> data){
  std::cout<<"calling abstract method pattern::receive_input(std::vector<double>&)"<<std::endl;
  return *this;
}

pattern & pattern::receive_ouput(std::vector<float> data){
  std::cout<<"calling abstract method pattern::receive_ouput(std::vector<double>&)"<<std::endl;
  return *this;
}

pattern & pattern::receive_input(std::istream & in){
  std::cout<<"calling abstract method pattern::receive_input(std::istream&)"<<std::endl;
  return *this;
}

pattern & pattern::receive_ouput(std::istream & in){
  std::cout<<"calling abstract method pattern::receive_ouput(std::istream&)"<<std::endl;
  return *this;
}

double pattern::input(int pos){
  std::cout<<"calling abstract method pattern::input(int)"<<std::endl;
  return 0;
}

float pattern::output(int pos){
  std::cout<<"calling abstract method pattern::output(int)"<<std::endl;
  return 0;
}

std::vector<double> & pattern::inputs(){
  std::cout<<"calling abstract method pattern::inputs()"<<std::endl;
  return _inputs;
}

std::vector<float> & pattern::outputs(){
  std::cout<<"calling abstract method pattern::outputs()"<<std::endl;
  return _outputs;
}

void pattern::print(){
  std::cout<<"calling abstract method pattern::print()"<<std::endl;
}

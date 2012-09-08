#include "neuron.hpp"

float neuron::_activation(double buffered){
  return activation::sigmoid(buffered);
}

neuron::neuron(int nbr_of_inputs){}

neuron::neuron(const neuron & source){}

neuron::~neuron(){}

neuron & neuron::operator=(neuron & source){
  std::cout<<"calling operator=(const neuron&) of abstract class neuron"<<std::endl;
  return *this;
}

neuron & neuron::operator>>(std::ostream & out){
  std::cout<<"calling operator>>(std::ostream&) of abstract class neuron"<<std::endl;

  return *this;
}

std::ostream & operator<<(std::ostream & out, neuron & cell){
  cell >> out;
  return out;
}

neuron & neuron::operator<<(double value){
  std::cout<<"calling operator<<(double) of abstract class neuron"<<std::endl;
  return *this;
}

neuron & neuron::operator<<(const std::vector<double> & data){
  std::cout<<"calling operator<<(const std::vector<double>&) of abstract class neuron"<<std::endl;
  return *this;
}

void neuron::rnd_weights(double min, double max){
  std::cout<<"calling rnd_weights(double, double) of abstract class neuron"<<std::endl;
}

void neuron::receive(double value){
  std::cout<<"calling method of abstract class neuron"<<std::endl;
}

void neuron::receive(const std::vector<double> & data){
  std::cout<<"calling receive(const std::vector<double> &) of abstract class neuron"<<std::endl;
}

float neuron::evaluate(){
  std::cout<<"calling evaluate() of abstract class neuron"<<std::endl;
  return neurals::UNEVALUATED;
}

bool neuron::is_active()const{
  std::cout<<"calling is_active()const; of abstract class neuron"<<std::endl;
  return false;
}

int neuron::input_index()const{
  std::cout<<"calling method of abstract class neuron"<<std::endl;
  return -1;
}

int neuron::size()const{
  std::cout<<"calling size()const; of abstract class neuron"<<std::endl;
  return -1;
}

void neuron::reset(){
  std::cout<<"calling neuron::reset() of abstract class neuron"<<std::endl;
}

void neuron::resize(int size, double minWeight, double maxWeight){
  std::cout<<"calling method neuron::resize(int,double,double) of abstract class neuron"<<std::endl;
}

float neuron::output()const{
  std::cout<<"calling method neuron::output()const; of abstract class neuron"<<std::endl;
  return neurals::UNEVALUATED;
}

double neuron::getBuffer()const{
  std::cout<<"calling method neuron::getBuffer()const; of abstract class neuron"<<std::endl;
  return 0;
}

short neuron::binary_output()const{
  std::cout<<"calling method neuron::binary_output()const; of abstract class neuron"<<std::endl;
  return neurals::UNEVALUATED;
}

double neuron::getWeight(int i){
  std::cout<<"calling method neuron::getWeight(int) of abstract class neuron"<<std::endl;
  return 0;
}

std::vector<double> neuron::weights(){
  std::cout<<"calling method neuron::weights() of abstract class neuron"<<std::endl;
  return std::vector<double>();
}

void neuron::setWeight(int i, double value){
  std::cout<<"calling method neuron::setWeight(int,double) of abstract class neuron"<<std::endl;
}

void neuron::print(){
  std::cout<<"calling method neuron::print() of abstract class neuron"<<std::endl;
}


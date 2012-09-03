#include "layer.hpp"

layer::layer(){}

layer::layer(int size, int neuron_size){}

layer::layer(const layer & source){}

layer::~layer(){}

layer & layer::operator=(layer & source){
  std::cout << "calling abstract layer::operator=(const layer&)" << std::endl;
  return *this;
}

neuron * layer::operator[](int pos){
  std::cout << "calling abstract layer::operator[](int)" << std::endl;
  return NULL;
}

layer & layer::operator>>(std::ostream & out){
  std::cout << "calling abstract layer::operator>>(std::ostream &)" << std::endl;
  return *this;
}

std::ostream & operator<<(std::ostream & out, layer * band){
  *band >> out;
  return out;
}


layer & layer::operator<<(double value){
  std::cout << "calling abstract layer::operator<<(double)" << std::endl;
  return *this;
}

layer & layer::operator<<(const std::vector<double> & data){
  std::cout << "calling abstract layer::operator<<(const std::vector<double>&)" << std::endl;
  return *this;
}

layer & layer::operator<<(neuron*){
  std::cout << "calling abstract layer::operator<<(neuron*)" << std::endl;
  return *this;
}

int layer::size()const{
  std::cout << "calling abstract layer::size()const" << std::endl;
  return -1;

}

void layer::resize(int newsize){
  std::cout << "calling abstract layer::resize(int)" << std::endl;
}

void layer::add(neuron* cell, int pos){
  std::cout << "calling abstract layer::add(neuron*,int)" << std::endl;
}

void layer::remove(int pos){
  std::cout << "calling abstract layer::remove(int)" << std::endl;
}

void layer::rnd_weights(double min, double max){
  std::cout << "calling abstract layer::rnd_weights(double,double)" << std::endl;
}

void layer::receive(double value){
  std::cout<<"calling abstract layer::receive(double)"<<std::endl;
}

void layer::receive(std::vector<double> data){
  std::cout<<"calling abstract layer::receive(std::vector<double>)"<<std::endl;
}

void layer::evaluate(){
  std::cout<<"calling abstract layer::evaluate()"<<std::endl;
}

std::vector<float> layer::output(){
  std::cout<<"calling abstract layer::output()"<<std::endl;
  return std::vector<float>();
}

void layer::reset(){
  std::cout<<"calling abstract layer::reset()"<<std::endl;
}

void layer::print(){
  std::cout<<"calling abstract layer::print()"<<std::endl;
}

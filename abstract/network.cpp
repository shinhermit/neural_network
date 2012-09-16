#include "network.hpp"

network::network(){}

network::network(int layers_num, int neurons_per_layer, int inputs_per_neuron){}

network::network(const network & source){}

network::~network(){}

network & network::operator=(network & source){
  std::cout<<"calling abstract network::operator=(network&)"<<std::endl;
  return *this;
}

layer * network::operator[](int i){
  std::cout<<"calling abstract network::operator[](int)"<<std::endl;
  return NULL;
}

neuron * network::operator()(int layer, int pos){
  std::cout<<"calling abstract network::operator()(int,int)"<<std::endl;
  return NULL;
}

network & network::operator>>(std::ostream & out){
  std::cout<<"calling abstract network::operator>>(std::ostream)"<<std::endl;
  return *this;
}

std::ostream & operator<<(std::ostream & out, network & net){
  net >> out;
  return out;
}

network & network::operator<<(layer* layer){
  std::cout<<"calling abstract network::operator<<(Layer*)"<<std::endl;
  return *this;
}

network & network::operator<<(double value){
  std::cout<<"calling abstract network::operator<<(double)"<<std::endl;
  return *this;
}

network & network::operator<<(std::vector<double> & data){
  std::cout<<"calling abstract network::operator<<(std::vector<double>&)"<<std::endl;
  return *this;
}


int network::size()const{
  std::cout<<"calling abstract network::size()const"<<std::endl;
  return -1;
}

std::map<int,synaptics> network::getConnections(){
  std::cout<<"calling abstract network::size()const"<<std::endl;
  return std::map<int,synaptics>();
}

void network::add_neuron(int layer, neuron * cell){
  std::cout<<"calling abstract network::add_neuron(int,neuron*)"<<std::endl;
}

void network::rmv_neuron(int layer, int pos){
  std::cout<<"calling abstract network::rmv_neuron(int,int)"<<std::endl;
}

void network::add_layer(layer * band, int pos){
  std::cout<<"calling abstract network::add_layer(layer*,int)"<<std::endl;
}

void network::rmv_layer(int layer){
  std::cout<<"calling abstract network::rmv_layer(int)"<<std::endl;
}

void network::add_layers(int how_many, int layer_size, int neuron_size){
  std::cout<<"calling abstract network::add_layers(int,int,int)"<<std::endl;
}

void network::rmv_layers(int begin, int end){
  std::cout<<"calling abstract network::rmv_layers(int,int)"<<std::endl;
}

bool network::valid_cell(int layer, int pos){
  std::cout<<"calling abstract network::valid_cell(int,int)"<<std::endl;
  return false;
}

int network::find_connection(int src_layer, int src_pos, int dst_layer, int dst_pos){
  std::cout<<"calling abstract network::find_connection(int,int, int,int)"<<std::endl;
  return -1;
}

bool network::has_connection(int src_layer, int src_pos, int dst_layer, int dst_pos){
  std::cout<<"calling abstract network::has_connection(int,int, int,int)"<<std::endl;
  return false;
}

void network::connect(int src_layer, int src_pos, int dst_layer, int dst_pos){
  std::cout<<"calling abstract network::connect(int,int, int,int)"<<std::endl;
}

void network::disconnect(int src_layer, int src_pos, int dst_layer, int dst_pos){
  std::cout<<"calling abstract network::disconnect(int,int, int,int)"<<std::endl;
}

void network::disconnect_incoming(int layer, int pos){
  std::cout<<"calling abstract network::disconnect_incoming(int,int)"<<std::endl;
}

void network::disconnect_outgoing(int layer, int pos){
  std::cout<<"calling abstract network::disconnect_outgoing(int,int)"<<std::endl;
}

void network::disconnect_all(int layer, int pos){
  std::cout<<"calling abstract network::disconnect_all(int,int)"<<std::endl;
}

void network::synaptic_injection(int layer){
  std::cout<<"calling abstract network::synaptic_injection(int)"<<std::endl;
}

std::vector<unit> network::succ(int src_layer, int src_pos){
  std::cout<<"calling abstract network::succ(int,int, neurals::type)"<<std::endl;
  return std::vector<unit>();
}

std::vector<unit> network::pred(int dst_layer, int dst_pos){
  std::cout<<"calling abstract network::pred(int,int)"<<std::endl;
  return std::vector<unit>();
}

void network::receive(double value){
  std::cout<<"calling abstract network::receive(double)"<<std::endl;
}

void network::receive(std::vector<double> data){
  std::cout<<"calling abstract network::receive(std::vector<double>)"<<std::endl;
}

void network::evaluate(){
  std::cout<<"calling abstract network::evaluate()"<<std::endl;
}

void network::evaluate(int num_of_times){
  std::cout<<"calling abstract network::evaluate(int)"<<std::endl;
}

std::vector<float> network::output(){
  std::cout<<"calling abstract network::output()"<<std::endl;
  return std::vector<float>();
}

void network::reset(){
  std::cout<<"calling abstract network::reset()"<<std::endl;
}

void network::clear_connections(){
  std::cout<<"calling abstract network::clear_connections()"<<std::endl;
}

void network::clear(){
  std::cout<<"calling abstract network::clear()"<<std::endl;
}

void network::save(std::ostream&){
  std::cout<<"calling abstract network::save(std::ostream&)"<<std::endl;
}

void network::load(std::istream&){
  std::cout<<"calling abstract network::load(std::istream&)"<<std::endl;
}

void network::print(){
  std::cout<<"calling abstract network::print()"<<std::endl;
}

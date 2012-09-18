#include "test_MLP_model.hpp"

void test_MLP_model(std::map<std::string,std::string> & args){
  network * p = new heavy_network();

  network & net = *p;

  std::cout<<std::endl<<"Creating a network with layers (2,3) (3,2) (2,3)..."<<std::endl;
  net << new heavy_layer(2, 3) << new heavy_layer(3, 2) << new heavy_layer(2,3);
  std::cout << net << std::endl;

  std::cout<<std::endl<<"Connecting as MLP..."<<std::endl;
  models::connect_MLP(net);
  std::cout << net <<std::endl;

  std::cout<<std::endl<<"Building (re-building) a MLP of 3 inputs and hidden layer of sizes 5..."<<std::endl;
  models::build_heavy_MLP(net, 3, 5, 4);
  std::cout << net << std::endl;

  delete p;

}


#include "test_MLP.hpp"
void test_MLP(std::vector<std::string>&){
  network * p = new heavy_network();
  network * q = new heavy_MLP();

  network & net = *p;
  network & mlp = *q;

  net << new heavy_layer(4,3) << new heavy_layer(2,4);
  models::connect_MLP(net);

  mlp = net;

  std::cout<<std::endl<<"Creating two different kinds of MLP with the same states..."<<std::endl;
  std::cout<<"network1:"<<std::endl;
  std::cout << net;
  std::cout<<"network2:"<<std::endl;
  std::cout << mlp;

  std::cout<<std::endl<<"Running evaluations on inputs 4.0 2.3 1.1..."<<std::endl;
  net << 4.0 << 2.3 << 1.1;
  mlp << 4.0 << 2.3 << 1.1;
  net.evaluate();
  mlp.evaluate();

  std::cout<<"network1:"<<std::endl;
  funcs::print_output(net);
  std::cout<<std::endl<<"network2:"<<std::endl;
  funcs::print_output(mlp);

  delete p;
  delete q;

}

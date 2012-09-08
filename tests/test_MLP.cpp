#include "heavy_network.hpp"
#include "heavy_MLP.hpp"
#include "models.hpp"
#include "funcs.hpp"

using namespace std;

int main(){
  network * p = new heavy_network();
  network * q = new heavy_MLP();

  network & net = *p;
  network & mlp = *q;

  net << new heavy_layer(4,3) << new heavy_layer(2,4);
  models::connect_MLP(net);

  mlp = net;

  cout<<endl<<"Creating two different kinds of MLP with the same states..."<<endl;
  cout<<"network1:"<<endl;
  cout << net;
  cout<<"network2:"<<endl;
  cout << mlp;

  cout<<endl<<"Running evaluations on inputs 4.0 2.3 1.1..."<<endl;
  net << 4.0 << 2.3 << 1.1;
  mlp << 4.0 << 2.3 << 1.1;
  net.evaluate();
  mlp.evaluate();

  cout<<"network1:"<<endl;
  funcs::print_output(net);
  cout<<endl<<"network2:"<<endl;
  funcs::print_output(mlp);

  delete p;
  delete q;

  return 0;
}

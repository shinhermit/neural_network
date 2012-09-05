#include "models.hpp"

using namespace std;

int main(){
  network * p = new heavy_network();

  network & net = *p;

  cout<<endl<<"Creating a network with layers (2,3) (3,2) (2,3)..."<<endl;
  net << new heavy_layer(2, 3) << new heavy_layer(3, 2) << new heavy_layer(2,3);
  cout << net << endl;

  cout<<endl<<"Connecting as MLP..."<<endl;
  models::connect_MLP(net);
  cout << net <<endl;

  cout<<endl<<"Building (re-building) a MLP of 3 inputs and layersof sizes 5, 9, 4..."<<endl;
  models::build_heavy_MLP(net, 3, 5, 9, 4);
  cout << net << endl;

  delete p;

  return 0;
}


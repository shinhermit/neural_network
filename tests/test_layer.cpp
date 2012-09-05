#include <iostream>
#include "heavy_layer.hpp"

using namespace std;

int main(){
  layer *p, *q;
  std::vector<double> data1, data2, data3;
  std::vector<float> output;
  int i, size;
  
  //homogenous layer
  cout<<endl<<"Creating an homogenous layer of 3 neurons each having 5 inputs..."<<endl;
  p =  new heavy_layer(3, 5);
  layer & band = *p;
  band.print();

  cout<<endl<<"Receiving a single value 0.1..."<<endl;
  band.receive(0.1);
  cout << band;

  cout<<endl<<endl<<"Receiving values 0.2, 0.3, 0.4 and 0.5..."<<endl;
  band<<0.2<<0.3<<0.4<<0.5;
  cout << band;

  cout<<endl<<endl<<"Evaluating the layer..."<<endl;
  band.evaluate();
  cout << band;

  cout<<endl<<endl<<"Receiving multiple values from vector (1.1, 1.2, 1.3, 1.4, 1.5)..."<<endl;
  for(i=1; i<=5; i++) data1.push_back(1+i*0.1);
  band << data1;
  cout << band;

  cout<<endl<<endl<<"Evaluating the layer"<<endl;
  band.evaluate();
  cout << band;

  cout<<endl<<endl<<"Receiving multiple vectors (2.1, 2.2) and (3.3, 3.4, 3.5)..."<<endl;
  for(i=1; i<=2; i++) data2.push_back(2+i*0.1);
  for(i=3; i<=5; i++) data3.push_back(3+i*0.1);
  band << data2 << data3;
  cout << band;

  cout<<endl<<endl<<"Evaluating the layer..."<<endl;
  band.evaluate();
  cout << band;

  cout<<endl<<endl<<"Printing output vector..."<<endl;
  output = band.output();
  size = output.size();
  cout<<"[";
  for(i=0; i<size-1; i++)
    cout<<output[i]<<" ";
  if(i<size)
    cout<<output[i];
  cout<<"]"<<endl;

  //non homogenous layer
  cout<<endl<<"Clearing the layer..."<<endl;
  band.resize(0);
  cout << band;

  cout<<endl<<endl<<"Adding a neuron of 3 inputs..."<<endl;
  band.add( new heavy_neuron(3) );
  cout << band;

  cout<<endl<<endl<<"Adding 2 neurons, 2 inputs and 4 inputs..."<<endl;
  band << new heavy_neuron(2) << new heavy_neuron(4);
  cout << band;

  cout<<endl<<endl<<"Inserting a neuron of 1 input at pos 1..."<<endl;
  band.add(new heavy_neuron(1), 1);
  cout << band;

  cout<<endl<<endl<<"Receiving values from vector (1 1 0 1)..."<<endl;
  data1 = vector<double>(1,1);
  data1[2] = 0;
  band << data1;
  cout << band;

  cout<<endl<<endl<<"Duplicating the layer..."<<endl;
  q = new heavy_layer();
  layer & copy = *q;
  copy = band;

  cout<<endl<<endl<<"Resetting one of the two layers..."<<endl;
  copy.reset();
  cout << "p1: " << band;
  cout << endl << "p2: " << copy;

  cout<<endl<<endl<<"Evaluating the other layer"<<endl;
  band.evaluate();
  cout << band << endl;

  delete p;
  delete q;

  return 0;
}

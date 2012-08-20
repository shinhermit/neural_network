#include <iostream>
#include "neuron.hpp"

using namespace std;

int main(){
  cout<<endl<<"Creating neuron(3)..."<<endl;
  neuron cell(3);
  cell.print();

  cout<<endl<<"receiving input 1.2 ..."<<endl;
  cell.receive(1.2);
  cout << cell;

  cout<<endl<<"receiving inputs 2.3 and 3.4 ..."<<endl;
  cell << 2.3 << 3.4;
  cout << cell;

  cout<<endl<<"running neural evaluation ..."<<endl;
  cell.evaluate();
  cout << cell;

  cout<<endl<<"receiving multiples inputs from vector (0.1, 0.2, 0.3) ..."<<endl;
  vector<double> data;
  data.push_back(0.1);
  data.push_back(0.2);
  data.push_back(0.3);
  cell<<data;
  cout << cell;

  cout<<endl<<"Running neural evaluation ..."<<endl;
  cell.evaluate();
  cout << cell;

  cout<<endl<<"changing weights ..."<<endl;
  cell.setWeight(1, 0.1);
  cell.setWeight(2, 0.2);
  cell.setWeight(3, 0.3);
  cout << cell;

  cout<<endl<<"testing observers methods ..."<<endl;
  cout<<"size(): "<<cell.size()<<endl;
  cout<<"input_index(): "<<cell.input_index()<<endl;
  cout<<"output(): "<<cell.output()<<endl;
  cout<<"binary_output(): "<<cell.binary_output()<<endl;
  cout<<"is_active(): "<<cell.is_active()<<endl;
  cout<<"getWeight() 1: "<<cell.getWeight(1)<<" | 2: "<<cell.getWeight(2)<<" | 3: "<<cell.getWeight(3)<<endl;
  return 0;
}

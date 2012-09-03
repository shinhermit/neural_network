#include <iostream>
#include "heavy_neuron.hpp"

using namespace std;

float sigmoid(double x){
  return 1 / ( 1 + exp(-1 * x) );
}

double weighted_sum(double a, double w_a, double b, double w_b, double c, double w_c, double biais){
  return a*w_a + b*w_b + c*w_c - biais;
}

int main(){
  cout<<endl<<"Creating a neuron with 3 inputs..."<<endl;
  neuron * cell = new heavy_neuron(3);
  cell->print();

  cout<<endl<<"receiving input 1.2 ..."<<endl;
  cell->receive(1.2);
  cout << cell << endl;

  cout<<endl<<"receiving inputs 2.3 and 3.4 ..."<<endl;
  *cell << 2.3 << 3.4;
  cout << cell << endl;

  cout<<endl<<"running neural evaluation ..."<<endl;
  cell->evaluate();
  cout << cell << endl;

  cout<<endl<<"receiving multiples inputs from vector (0.1, 0.2, 0.3) ..."<<endl;
  vector<double> data;
  data.push_back(0.1);
  data.push_back(0.2);
  data.push_back(0.3);
  *cell << data;
  cout << cell << endl;

  cout<<endl<<"Running neural evaluation ..."<<endl;
  cell->evaluate();
  cout << cell << endl;

  cout<<endl<<"changing weights ..."<<endl;
  cell->setWeight(0, 0.4);
  cell->setWeight(1, 0.1);
  cell->setWeight(2, 0.2);
  cell->setWeight(3, 0.3);
  cout << cell << endl;

  cout<<endl<<"Comparison of neuron's outputs to expected output ..."<<endl;
  double sum;
  *cell << 1.1 << 1.2 << 1.3;
  cout << cell << endl;
  cell->evaluate();
  sum = weighted_sum(1.1, 0.1, 1.2,0.2, 1.3,0.3, 0);
  cout<<"inputs 1.1, 1.2, 1.3 --> "<<cell->output()<<"   expected weighted sum: "<<sum<<"   expected output: "<<sigmoid(sum-0.4)<<endl;

  cout<<endl<<"testing observers methods ..."<<endl;
  cout<<"size(): "<<cell->size()<<endl;
  cout<<"input_index(): "<<cell->input_index()<<endl;
  cout<<"output(): "<<cell->output()<<endl;
  cout<<"binary_output(): "<<cell->binary_output()<<endl;
  cout<<"is_active(): "<<cell->is_active()<<endl;
  cout<<"getWeight() 1: "<<cell->getWeight(1)<<" | 2: "<<cell->getWeight(2)<<" | 3: "<<cell->getWeight(3)<<endl;
  return 0;

  delete cell;
}

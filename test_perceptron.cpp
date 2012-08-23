#include <iostream>
#include "perceptron.hpp"

using namespace std;

int main(){
  std::vector<double> data1, data2, data3;
  std::vector<float> output;
  int i, size;
  
  //homogenous perceptron
  cout<<endl<<"Creating an homogenous perceptron of 3 neurons each having 5 inputs..."<<endl;
  perceptron perceptor(3, 5);
  perceptor.print();

  cout<<endl<<"Receiving a single value 0.1..."<<endl;
  perceptor.receive(0.1);
  cout << perceptor;

  cout<<endl<<endl<<"Receiving values 0.2, 0.3, 0.4 and 0.5..."<<endl;
  perceptor<<0.2<<0.3<<0.4<<0.5;
  cout << perceptor;

  cout<<endl<<endl<<"Evaluating the perceptron..."<<endl;
  perceptor.evaluate();
  cout << perceptor;

  cout<<endl<<endl<<"Receiving multiple values from vector (1.1, 1.2, 1.3, 1.4, 1.5)..."<<endl;
  for(i=1; i<=5; i++) data1.push_back(1+i*0.1);
  perceptor << data1;
  cout << perceptor;

  cout<<endl<<endl<<"Evaluating the perceptron"<<endl;
  perceptor.evaluate();
  cout << perceptor;

  cout<<endl<<endl<<"Receiving multiple vectors (2.1, 2.2) and (3.3, 3.4, 3.5)..."<<endl;
  for(i=1; i<=2; i++) data2.push_back(2+i*0.1);
  for(i=3; i<=5; i++) data3.push_back(3+i*0.1);
  perceptor << data2 << data3;
  cout << perceptor;

  cout<<endl<<endl<<"Evaluating the perceptron..."<<endl;
  perceptor.evaluate();
  cout<<perceptor;

  cout<<endl<<endl<<"Printing output vector..."<<endl;
  output = perceptor.output();
  size = output.size();
  cout<<"[";
  for(i=0; i<size-1; i++)
    cout<<output[i]<<" ";
  if(i<size)
    cout<<output[i];
  cout<<"]"<<endl;

  //non homogenous perceptron
  cout<<endl<<"Creating an empty perceptron..."<<endl;
  perceptor = perceptron();
  cout << perceptor;

  cout<<endl<<endl<<"Adding a neuron of 3 inputs..."<<endl;
  perceptor.add(neuron(3));
  cout << perceptor;

  cout<<endl<<endl<<"Adding 2 neurons, 2 inputs and 4 inputs..."<<endl;
  perceptor << neuron(2) << neuron(4);
  cout << perceptor;

  cout<<endl<<endl<<"Inserting a neuron of 1 input at pos 1..."<<endl;
  perceptor.add(neuron(1), 1);
  cout << perceptor;

  cout<<endl<<endl<<"Receiving values from vector (1 1 0 1)..."<<endl;
  data1 = vector<double>(1,1);
  data1[2] = 0;
  perceptor << data1;
  cout << perceptor;

  cout<<endl<<endl<<"Duplicating the perceptron..."<<endl;
  perceptron copy(perceptor);

  cout<<endl<<endl<<"Resetting one of the two perceptrons..."<<endl;
  copy.reset();
  cout << "p1: " << perceptor;
  cout << endl << "p2: " << copy;

  cout<<endl<<endl<<"Evaluating the other perceptron"<<endl;
  perceptor.evaluate();
  cout << perceptor << endl;
  return 0;
}

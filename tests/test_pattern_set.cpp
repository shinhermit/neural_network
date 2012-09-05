#include "h_pattern_set.hpp"

using namespace std;

int main(){
  pattern_set *  p = new h_pattern_set();

  pattern_set & pset = *p;

  cout<<endl<<endl<<"Creating empty set of examples..."<<endl;
  cout << pset;

  cout<<endl<<endl<<"Adding an example with input values 0.1, 0.2, 0.3..."<<endl;
  cout<<"and expected ouputs 1.1, 1.2, 1.3..."<<endl;
  pset << new h_pattern();
  pset[0]->receive_input(0.1) << 0.2 << 0.3;
  pset[0]->receive_output(1.1)(1.2)(1.3);
  cout << pset;

  cout<<endl<<endl<<"Adding an example with input values -3.1, 3.2, -3.3..."<<endl;
  cout<<"and expected ouputs 0.51, -0.52, 0.53..."<<endl;
  pset << new h_pattern();
  pset[1]->receive_input(-3.1) << 3.2 << -3.3;
  pset[1]->receive_output(0.51)(-0.52)(0.53);
  cout << pset;

  cout<<endl<<endl<<"Adding an example with input values -3.1, 4.1, -5.6..."<<endl;
  cout<<"and expected ouputs -0.3, -0.1, -0.4..."<<endl;
  pset << new h_pattern();
  pset[2]->receive_input(-3.1) << 4.1 << -5.6;
  pset[2]->receive_output(-0.3)(-0.1)(-0.4);
  cout << pset;

  cout<<endl<<endl<<"Accessing pattern 2..."<<endl;
  cout << *pset[1];

  cout<<endl<<endl<<"Accessing expected output 1 of pattern 3"<<endl;
  cout << pset[2]->output(0);
  cout<<endl<<endl;

  delete p;

  return 0;
}

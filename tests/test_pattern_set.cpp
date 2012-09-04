#include "h_pattern_set.hpp"

using namespace std;

int main(){
  pattern_set *  set;
  pattern * example;

  cout<<endl<<endl<<"Creating empty set of examples..."<<endl;
  set = new h_pattern_set();
  cout << set;

  cout<<endl<<endl<<"Adding an example with input values 0.1, 0.2, 0.3..."<<endl;
  cout<<"and expected ouputs 1.1, 1.2, 1.3..."<<endl;
  example = new h_pattern();
  *example << 0.1 << 0.2 << 0.3;
  (*example)(1.1)(1.2)(1.3);
  *set << example;
  cout << set;

  cout<<endl<<endl<<"Adding an example with input values -3.1, 3.2, -3.3..."<<endl;
  cout<<"and expected ouputs 0.51, -0.52, 0.53..."<<endl;
  example = new h_pattern();
  *example << -3.1 << 3.2 << -3.3;
  (*example)(0.51)(-0.52)(0.53);
  *set << example;
  cout << set;

  cout<<endl<<endl<<"Adding an example with input values -3.1, 4.1, -5.6..."<<endl;
  cout<<"and expected ouputs -0.3, -0.1, -0.4..."<<endl;
  example = new h_pattern();
  *example << -3.1 << 4.1 << -5.6;
  (*example)(-0.3)(-0.1)(-0.4);
  *set << example;
  cout << set;

  cout<<endl<<endl<<"Accessing pattern 2..."<<endl;
  cout << (*set)[1];

  cout<<endl<<endl<<"Accessing expected output 1 of pattern 3"<<endl;
  cout << (*set)[2]->output(0);
  cout<<endl<<endl;

  delete set;

  return 0;
}

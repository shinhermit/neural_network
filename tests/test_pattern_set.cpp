#include "test_pattern_set.hpp"

void test_pattern_set(std::vector<std::string> & args){
  pattern_set *  p = new h_pattern_set();

  pattern_set & pset = *p;

  std::cout<<std::endl<<std::endl<<"Creating empty set of examples..."<<std::endl;
  std::cout << pset;

  std::cout<<std::endl<<std::endl<<"Adding an example with input values 0.1, 0.2, 0.3..."<<std::endl;
  std::cout<<"and expected ouputs 1.1, 1.2, 1.3..."<<std::endl;
  pset << new h_pattern();
  pset[0]->receive_input(0.1) << 0.2 << 0.3;
  pset[0]->receive_output(1.1)(1.2)(1.3);
  std::cout << pset;

  std::cout<<std::endl<<std::endl<<"Adding an example with input values -3.1, 3.2, -3.3..."<<std::endl;
  std::cout<<"and expected ouputs 0.51, -0.52, 0.53..."<<std::endl;
  pset << new h_pattern();
  pset[1]->receive_input(-3.1) << 3.2 << -3.3;
  pset[1]->receive_output(0.51)(-0.52)(0.53);
  std::cout << pset;

  std::cout<<std::endl<<std::endl<<"Adding an example with input values -3.1, 4.1, -5.6..."<<std::endl;
  std::cout<<"and expected ouputs -0.3, -0.1, -0.4..."<<std::endl;
  pset << new h_pattern();
  pset[2]->receive_input(-3.1) << 4.1 << -5.6;
  pset[2]->receive_output(-0.3)(-0.1)(-0.4);
  std::cout << pset;

  std::cout<<std::endl<<std::endl<<"Accessing pattern 2..."<<std::endl;
  std::cout << *pset[1];

  std::cout<<std::endl<<std::endl<<"Accessing expected output 1 of pattern 3"<<std::endl;
  std::cout << pset[2]->output(0);
  std::cout<<std::endl<<std::endl;

  delete p;

}

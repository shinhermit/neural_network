#include "test_pattern.hpp"

void test_pattern(std::map<std::string,std::string> & args){
  pattern * p;

  std::cout<<std::endl<<std::endl<<"Creating empty example..."<<std::endl;
  p = new h_pattern();
  pattern & example = *p;
  std::cout << example;

  std::cout<<std::endl<<std::endl<<"Adding input values 0.1, 0.2, 0.3..."<<std::endl;
  example << 0.1 << 0.2 << 0.3;
  std::cout << example;

  std::cout<<std::endl<<std::endl<<"Adding expected ouputs 1.1, 1.2, 1.3..."<<std::endl;
  example(1.1)(1.2)(1.3);
  std::cout << example;

  std::cout<<std::endl<<std::endl<<"Accessing data..."<<std::endl;
  std::cout << "first data: "<<example.input(0)<<std::endl;
  std::cout << "second expected ouput: "<<example.output(1)<<std::endl<<std::endl;

  example.clear();

  std::cout<<std::endl<<std::endl<<"Adding inputs and outputs from a file..."<<std::endl;
  std::ifstream ifile("res/xor", std::ifstream::in);
  example.receive_inputs(ifile);
  example.receive_outputs(ifile);
  std::cout << example;
  ifile.close();

  std::cout<<std::endl<<std::endl<<"Adding expected ouputs from std::cin..."<<std::endl;
  example.receive_outputs(std::cin);
  std::cout << example;

  delete p;

}

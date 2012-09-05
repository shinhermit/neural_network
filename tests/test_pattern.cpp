#include "h_pattern.hpp"

#include <fstream>
#include <sstream>

using namespace std;

int main(){
  pattern * p;

  cout<<endl<<endl<<"Creating empty example..."<<endl;
  p = new h_pattern();
  pattern & example = *p;
  cout << example;

  cout<<endl<<endl<<"Adding input values 0.1, 0.2, 0.3..."<<endl;
  example << 0.1 << 0.2 << 0.3;
  cout << example;

  cout<<endl<<endl<<"Adding expected ouputs 1.1, 1.2, 1.3..."<<endl;
  example(1.1)(1.2)(1.3);
  cout << example;

  cout<<endl<<endl<<"Accessing data..."<<endl;
  cout << "first data: "<<example.input(0)<<endl;
  cout << "second expected ouput: "<<example.output(1)<<endl<<endl;

  example.clear();

  cout<<endl<<endl<<"Adding inputs and outputs from a file..."<<endl;
  ifstream ifile("res/xor", ifstream::in);
  example.receive_inputs(ifile);
  example.receive_outputs(ifile);
  cout << example;
  ifile.close();

  cout<<endl<<endl<<"Adding expected ouputs from std::cin..."<<endl;
  example.receive_outputs(cin);
  cout << example;

  delete p;

  return 0;
}

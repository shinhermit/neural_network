#include "learning.hpp"
#include "funcs.hpp"
#include "models.hpp"

#include <fstream>

using namespace std;

int main(){
  network * p = new heavy_network();
  pattern_set * q = new h_pattern_set();
  ifstream ifile;
  int i, N, size;
  double alpha;

  try{
  //Building the network
  network & net = *p;

  cout<<endl<<"Building a MLP network..."<<endl;
  cout << "Enter: hidden_layer_size ";
  cin >> size;
  models::build_heavy_MLP(net, 2, size, 4);
  cout << net;

  //Getting examples
  pattern_set & examples = *q;

  ifile.open("res/xor2");
  if( ! ifile.is_open() ) cout<<"could not open file"<<endl;
  i = 0;
  while( !ifile.eof() ){
    examples << new h_pattern();
    examples[i]->receive_inputs(ifile);
    examples[i]->receive_outputs(ifile);
    i++;
  }
  ifile.close();
  cout << "Getting examples from file..."<<endl;
  cout << examples;

  //evaluation before learning
  cout<<endl<<"Before learning..."<<endl;
  net << 0.0 << 0.0;
  net.evaluate();
  cout<<"evaluate(0,0) --> ";
  funcs::print_output(net);

  net << 0.0 << 1.0;
  net.evaluate();
  cout<<"evaluate(0,1) --> ";
  funcs::print_output(net);

  net << 1.0 << 0.0;
  net.evaluate();
  cout<<"evaluate(1,0) --> ";
  funcs::print_output(net);

  net << 1.0 << 1.0;
  net.evaluate();
  cout<<"evaluate(1,1) --> ";
  funcs::print_output(net);

  //first learning
  cout<<endl<<endl<<"Learning rate? "<<endl;
  cin >> alpha;
  learning::backpropagation(alpha, net, examples);

  //evaluation after first learning
  cout<<endl<<endl<<"After first learning..."<<endl;
  net << 0.0 << 0.0;
  net.evaluate();
  cout<<"evaluate(0,0) --> ";
  funcs::print_output(net);

  net << 0.0 << 1.0;
  net.evaluate();
  cout<<"evaluate(0,1) --> ";
  funcs::print_output(net);

  net << 1.0 << 0.0;
  net.evaluate();
  cout<<"evaluate(1,0) --> ";
  funcs::print_output(net);

  net << 1.0 << 1.0;
  net.evaluate();
  cout<<"evaluate(1,1) --> ";
  funcs::print_output(net);

  //N successive learnings
  cout<<"How many more iterations? ";
  cin >> N;
  for(i=0; i<N; i++)
    learning::backpropagation(alpha, net, examples);

  //evaluation after first learning
  cout<<endl<<endl<<"After "<<N<<" more learnings..."<<endl;
  net << 0.0 << 0.0;
  net.evaluate();
  cout<<"evaluate(0,0) --> ";
  funcs::print_output(net);

  net << 0.0 << 1.0;
  net.evaluate();
  cout<<"evaluate(0,1) --> ";
  funcs::print_output(net);

  net << 1.0 << 0.0;
  net.evaluate();
  cout<<"evaluate(1,0) --> ";
  funcs::print_output(net);

  net << 1.0 << 1.0;
  net.evaluate();
  cout<<"evaluate(1,1) --> ";
  funcs::print_output(net);
  }
  catch(std::string e){
    cout << "Caught " << e << endl;
  }

  delete p;
  delete q;

  return 0;
}

#include "test_neuron.hpp"

double weighted_sum(double a, double w_a, double b, double w_b, double c, double w_c, double biais){
  return a*w_a + b*w_b + c*w_c - biais;
}

void test_neuron(std::vector<std::string> & args){
  std::ofstream ofile;
  std::ifstream ifile;
  std::string filename;
  neuron * p = new heavy_neuron(3);
  neuron & cell = *p;

  std::cout<<std::endl<<"Creating a neuron with 3 inputs..."<<std::endl;

  cell.print();

  std::cout<<std::endl<<"receiving input 1.2 ..."<<std::endl;
  cell.receive(1.2);
  std::cout << cell << std::endl;

  std::cout<<std::endl<<"receiving inputs 2.3 and 3.4 ..."<<std::endl;
  cell << 2.3 << 3.4;
  std::cout << cell << std::endl;

  std::cout<<std::endl<<"running neural evaluation ..."<<std::endl;
  cell.evaluate();
  std::cout << cell << std::endl;

  std::cout<<std::endl<<"receiving multiples inputs from std::vector (0.1, 0.2, 0.3) ..."<<std::endl;
  std::vector<double> data;
  data.push_back(0.1);
  data.push_back(0.2);
  data.push_back(0.3);
  cell << data;
  std::cout << cell << std::endl;

  std::cout<<std::endl<<"Running neural evaluation ..."<<std::endl;
  cell.evaluate();
  std::cout << cell << std::endl;

  std::cout<<std::endl<<"changing weights ..."<<std::endl;
  cell.setWeight(0, 0.4);
  cell.setWeight(1, 0.1);
  cell.setWeight(2, 0.2);
  cell.setWeight(3, 0.3);
  std::cout << cell << std::endl;

  std::cout<<std::endl<<"Comparison of neuron's outputs to expected output ..."<<std::endl;
  double sum;
  cell << 1.1 << 1.2 << 1.3;
  std::cout << cell << std::endl;
  cell.evaluate();
  sum = weighted_sum(1.1, 0.1, 1.2,0.2, 1.3,0.3, 0);
  std::cout<<"inputs 1.1, 1.2, 1.3 --> "<<cell.output()<<"   expected weighted sum: "<<sum<<"   expected output: "<<activation::sigmoid(sum-0.4)<<std::endl;

  std::cout<<std::endl<<"testing observers methods ..."<<std::endl;
  std::cout<<"size(): "<<cell.size()<<std::endl;
  std::cout<<"input_index(): "<<cell.input_index()<<std::endl;
  std::cout<<"output(): "<<cell.output()<<std::endl;
  std::cout<<"binary_output(): "<<cell.binary_output()<<std::endl;
  std::cout<<"is_active(): "<<cell.is_active()<<std::endl;
  std::cout<<"getWeight() 1: "<<cell.getWeight(1)<<" | 2: "<<cell.getWeight(2)<<" | 3: "<<cell.getWeight(3)<<std::endl;

  std::cout<<std::endl<<"Saving to  file save_neuron.neu..."<<std::endl;

  filename = "res/save_neuron.neu";

  ofile.open( filename.c_str() );
  if( ofile.is_open() ){
    cell.save(ofile);
    ofile.close();
  }  

  std::cout<<std::endl<<"Loading from file neuron.neu..."<<std::endl;
  filename = "res/neuron.neu";
  ifile.open( filename.c_str() );
  if( ifile.is_open() ){
    cell.load(ifile);
    ifile.close();
  }

  std::cout << cell << std::endl;

  delete p;
}

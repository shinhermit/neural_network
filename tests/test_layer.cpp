#include "test_layer.hpp"

void test_layer(std::vector<std::string> & args){
  layer *p, *q;
  std::vector<double> data1, data2, data3;
  std::vector<float> output;
  int i, size;
  std::ifstream ifile;
  std::ofstream ofile;
  std::string filename;
  
  //homogenous layer
  std::cout<<std::endl<<"Creating an homogenous layer of 3 neurons each having 5 inputs..."<<std::endl;
  p =  new heavy_layer(3, 5);
  layer & band = *p;
  band.print();

  std::cout<<std::endl<<"Receiving a single value 0.1..."<<std::endl;
  band.receive(0.1);
  std::cout << band;

  std::cout<<std::endl<<std::endl<<"Receiving values 0.2, 0.3, 0.4 and 0.5..."<<std::endl;
  band<<0.2<<0.3<<0.4<<0.5;
  std::cout << band;

  std::cout<<std::endl<<std::endl<<"Evaluating the layer..."<<std::endl;
  band.evaluate();
  std::cout << band;

  std::cout<<std::endl<<std::endl<<"Receiving multiple values from std::vector (1.1, 1.2, 1.3, 1.4, 1.5)..."<<std::endl;
  for(i=1; i<=5; i++) data1.push_back(1+i*0.1);
  band << data1;
  std::cout << band;

  std::cout<<std::endl<<std::endl<<"Evaluating the layer"<<std::endl;
  band.evaluate();
  std::cout << band;

  std::cout<<std::endl<<std::endl<<"Receiving multiple std::vectors (2.1, 2.2) and (3.3, 3.4, 3.5)..."<<std::endl;
  for(i=1; i<=2; i++) data2.push_back(2+i*0.1);
  for(i=3; i<=5; i++) data3.push_back(3+i*0.1);
  band << data2 << data3;
  std::cout << band;

  std::cout<<std::endl<<std::endl<<"Evaluating the layer..."<<std::endl;
  band.evaluate();
  std::cout << band;

  std::cout<<std::endl<<std::endl<<"Printing output std::vector..."<<std::endl;
  output = band.output();
  size = output.size();
  std::cout<<"[";
  for(i=0; i<size-1; i++)
    std::cout<<output[i]<<" ";
  if(i<size)
    std::cout<<output[i];
  std::cout<<"]"<<std::endl;

  //non homogenous layer
  std::cout<<std::endl<<"Clearing the layer..."<<std::endl;
  band.resize(0);
  std::cout << band;

  std::cout<<std::endl<<std::endl<<"Adding a neuron of 3 inputs..."<<std::endl;
  band.add( new heavy_neuron(3) );
  std::cout << band;

  std::cout<<std::endl<<std::endl<<"Adding 2 neurons, 2 inputs and 4 inputs..."<<std::endl;
  band << new heavy_neuron(2) << new heavy_neuron(4);
  std::cout << band;

  std::cout<<std::endl<<std::endl<<"Inserting a neuron of 1 input at pos 1..."<<std::endl;
  band.add(new heavy_neuron(1), 1);
  std::cout << band;

  std::cout<<std::endl<<std::endl<<"Receiving values from std::vector (1 1 0 1)..."<<std::endl;
  data1 = std::vector<double>(1,1);
  data1[2] = 0;
  band << data1;
  std::cout << band;

  std::cout<<std::endl<<std::endl<<"Duplicating the layer..."<<std::endl;
  q = new heavy_layer();
  layer & copy = *q;
  copy = band;

  std::cout<<std::endl<<std::endl<<"Resetting one of the two layers..."<<std::endl;
  copy.reset();
  std::cout << "p1: " << band;
  std::cout << std::endl << "p2: " << copy;

  std::cout<<std::endl<<std::endl<<"Evaluating the other layer"<<std::endl;
  band.evaluate();
  std::cout << band << std::endl;

  filename = "res/save_layer.lay";
  std::cout<<std::endl<<std::endl<<"saving layer to file "<<filename<<"..."<<std::endl;
  ofile.open( filename.c_str() );
  if( ofile.is_open() ){
    band.save(ofile);
    ofile.close();
  }

  filename = "res/layer.lay";
  std::cout<<std::endl<<std::endl<<"Loading layer from file "<<filename<<"..."<<std::endl;
  ifile.open( filename.c_str() );
  if( ifile.is_open() ){
    band.load(ifile);
    ifile.close();
  }
  std::cout << band << std::endl;

  delete p;
  delete q;

}

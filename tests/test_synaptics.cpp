#include "test_synaptics.hpp"

void test_synaptics(std::vector<std::string> & args){
  int i, layer, position;
  unit src, dst;
  synaptics synapses;
  std::string filename;
  std::ifstream ifile;
  std::ofstream ofile;

  //asking data for 3 connections to the user
  std::cout<<std::endl<<"Creation of 3 connections..."<<std::endl;
  for(i=0; i<3; i++){
    std::cout<<"connection "<<i+1<<std::endl;

    std::cout<<"layer where the source unit is: ";
    std::cin>>layer;
    std::cout<<"position in the layer: ";
    std::cin>>position;
    src = unit(layer, position);

    std::cout<<"layer where the destination unit is: ";
    std::cin>>layer;
    std::cout<<"position in the layer: ";
    std::cin>>position;
    dst = unit(layer, position);

    synapses << synaptic(src, dst);
  }

  std::cout<<std::endl<<"Using operator []..."<<std::endl;
  std::cout<<"synapses[0] == synapses[1] : ";
  if(synapses[0] == synapses[1])
    std::cout<<"true"<<std::endl;
  else
    std::cout<<"false"<<std::endl;

  std::cout<<std::endl<<"printing synapses ..."<<std::endl;
  std::cout << synapses << std::endl;

  filename = "res/save_synaptics.syn";
  std::cout<<std::endl<<"Saving to file "<<filename<<" ..."<<std::endl;
  ofile.open( filename.c_str() );
  if( ofile.is_open() ){
    synapses.save(ofile);
    ofile.close();
  }

  filename = "res/synaptics.syn";
  std::cout<<std::endl<<"Loading from file "<<filename<<" ..."<<std::endl;
  ifile.open( filename.c_str() );
  if( ifile.is_open() ){
    synapses.load(ifile);
    ifile.close();
  }
  std::cout << synapses << std::endl;
}

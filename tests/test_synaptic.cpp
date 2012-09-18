#include "test_synaptic.hpp"

void test_synaptic(std::map<std::string,std::string> & args){
  int i, layer, position;
  unit src, dst;
  synaptic synapses[3];

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

    synapses[i] = synaptic(src, dst);
  }

  std::cout<<std::endl<<"Comparing the connections..."<<std::endl;
  std::cout<<"synapse1 == synapse2 : ";
  if(synapses[0] == synapses[1])
    std::cout<<"true"<<std::endl;
  else
    std::cout<<"false"<<std::endl;

  std::cout<<"synapse1 < synapse3 : ";
  if(synapses[0] < synapses[2])
    std::cout<<"true"<<std::endl;
  else
    std::cout<<"false"<<std::endl;

  std::cout<<"synapse2 <= synapse3 : ";
  if(synapses[1] <= synapses[2])
    std::cout<<"true"<<std::endl;
  else
    std::cout<<"false"<<std::endl;

  std::cout<<std::endl<<"printing synapses ..."<<std::endl;
  std::cout<<"1: "<<synapses[0]<<std::endl;
  std::cout<<"2: "<<synapses[1]<<std::endl;
  std::cout<<"3: "<<synapses[2]<<std::endl;

  std::cout<<std::endl<<"unsing layer(), source() and dest() observers ..."<<std::endl;
  std::cout<<"1: layer() -> "<<synapses[0].layer()<<" | source() -> "<<synapses[0].source()<<" | dest() -> "<<synapses[0].dest()<<std::endl;

}

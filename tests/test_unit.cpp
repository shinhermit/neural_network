#include "test_unit.hpp"

void test_unit(std::map<std::string,std::string> & args){
  int i, layer, position;
  unit units[3];

  //asking data for 3 units to the user
  std::cout<<std::endl<<"Creation of 3 units..."<<std::endl;
  for(i=0; i<3; i++){
    std::cout<<"layer where the unit "<<i+1<<" is: ";
    std::cin>>layer;
    std::cout<<"position in the layer: ";
    std::cin>>position;
    units[i] = unit(layer,position);
  }

  std::cout<<std::endl<<"Comparing the units..."<<std::endl;
  std::cout<<"unit1 == unit2 : ";
  if(units[0] == units[1])
    std::cout<<"true"<<std::endl;
  else
    std::cout<<"false"<<std::endl;

  std::cout<<"unit1 < unit3 : ";
  if(units[0] < units[2])
    std::cout<<"true"<<std::endl;
  else
    std::cout<<"false"<<std::endl;

  std::cout<<"unit2 >= unit3 : ";
  if(units[1] >= units[2])
    std::cout<<"true"<<std::endl;
  else
    std::cout<<"false"<<std::endl;

  std::cout<<std::endl<<"printing units ..."<<std::endl;
  std::cout<<"1: "; units[0].print(); std::cout<<std::endl;
  std::cout<<"2: "<<units[1]<<std::endl;
  std::cout<<"3: "<<units[2]<<std::endl;

  std::cout<<std::endl<<"unsing layer() and pos() observers ..."<<std::endl;
  std::cout<<"1: layer() -> "<<units[0].layer()<<" | pos() -> "<<units[0].pos()<<std::endl;

}

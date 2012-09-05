#include "funcs.hpp"

namespace funcs
{
  void print_output(network & net){
    int i, size;
    std::vector<float> output;

    output = net.output();
    size = output.size();
    std::cout<<"[";
    for(i=0; i<size-1; i++)
      std::cout<<output[i]<<" ";
    if(i<size)
      std::cout<<output[i];
    std::cout<<"]"<<std::endl;
  }
};


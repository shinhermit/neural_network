#include "funcs.hpp"

namespace funcs
{

  float sigmoid(double x){
    return 1/( 1 + exp(-x) );
  }

  float sigmoid_derivative(double x){
    return sigmoid(x) * ( 1 - sigmoid(x) );
  }

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


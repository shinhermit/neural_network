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


  int find_args(int argc, char** argv, std::string param_tag){
    int i;
    bool found;

    if(argc > 1){
      i = 0;
      found = false;
      while( i < argc && !found ){

	if( strcmp( argv[i], param_tag.c_str() ) != 0 ){
	  found = true;
	}
	else{
	  i++;
	}
      }

      return i+2;

    }
    else{
      return -1;
    }

  }

};


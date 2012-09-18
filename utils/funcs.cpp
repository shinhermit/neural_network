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

  void parse_cmd_line(int argc, char** argv, std::map<std::string,std::string> & args){
    int i, k;
    bool goHead;
    std::string option, value;

    i=1;
    while(i < argc){
      if(argv[i][0] == '-'){

	  k = i + 1;
	if(i+1 < argc){
	  option = argv[i];
	  goHead = true;
	  while(k < argc && goHead){

	    if(argv[k][0] == '-'){
	      goHead = false;
	    }
	    else{

	      value = argv[k];

	      if( args.count(option) ){
		args[option] += " " + value;
	      }
	      else{
		args.insert( std::pair<std::string,std::string>(option,value) );
	      }

	      k++;
	    }

	  }//end while !is_option(argv[k])
	}//end if more_cmd_args()

      }//end if is_option(argv[i])
      else{
	i++;
      }
      i = k;

    }//end while i < argc

  }

};


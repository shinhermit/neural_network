#include "test_backprop.hpp"

void evaluate_few_examples(network & net, pattern_set & set, int how_many){
  int i, size;
  std::vector<float> output;

  size = set.size();
  i=0;
  while(i < size && i < how_many){

    net << set[i]->inputs();
    net.evaluate();
    output = net.output();

    std::cout << "Example:" << std::endl;
    std::cout << *set[i];

    std::cout << "Output of the network:";
    std::cout << "[";
    easyContainers::print_vector<float>(output);
    std::cout << "]" << std::endl;

    i++;
  }

}

void test_backprop(std::vector<std::string> & args){
  network * p = new heavy_network();
  pattern_set * q = new h_pattern_set();
  std::ifstream ifile;
  int i, argc, layer_size, last, neurons_size, default_input_size, few_examples, N;
  double alpha, default_rate;
  std::string filename, default_file, ans;
  std::istringstream iss;

  network & net = *p;
  pattern_set & examples = *q;

  default_input_size = 3;
  default_rate = 0.5;
  default_file = "res/xor";

  argc = args.size();


  //ressources file (examples)
  i = 0;
  if(i < argc){
    filename = args[i];
    i++;
  }
  else{
    filename = default_file;
  }

  //learning rate
  if(i < argc){
    iss.str(args[i]);
    iss >> alpha;
    i++;
  }
  else{
    alpha = default_rate;
  }

  //Building the network

  while(i < argc){
    iss.clear();
    iss.str(args[i]);
    iss >> layer_size;

    i++;
    if(i < argc){
      iss.clear();
      iss.str(args[i]);
      iss >> neurons_size;
    }
    else{
      if(net.size() > 0){
	last = net.size() - 1;
	if(net[last]->size() > 0 ){
	  neurons_size = net(last,0)->size();
	}
	else{
	  neurons_size = default_input_size;
	}
      }
      else{
	neurons_size = default_input_size;
      }
    }

    net << new heavy_layer(layer_size, neurons_size);

    i++;
  }

  //checking parsed arguments

  if( net.size() < 1 ){
    std::cout << "Add at least one layer."<<std::endl<<"Enter layer_size neurons_size: ";
    std::cin >> layer_size >> neurons_size;

    net << new heavy_layer(layer_size, neurons_size);

    std::cout << "Add More layers ? y/n _";
    std::cin >> ans;
    while(ans == "y" || ans == "Y"){
      std::cout<<"Enter layer_size neurons_size: ";
      std::cin >> layer_size >> neurons_size;

      net << new heavy_layer(layer_size, neurons_size);

      std::cout << "Add More layers ? y/n _";
      std::cin >> ans;
    }
  }

  if(alpha > 1 || alpha <=0){
    std::cout<<"bad value for learning rate. Set to default value "<<default_rate<<std::endl;
    alpha = default_rate;
  }

  //now we begin

  models::connect_MLP(net);
  std::cout << "Building MLP model from generic network.... "<<std::endl;
  std::cout << net;


  //Getting examples

  //possible issue: check if file exists
  ifile.open( filename.c_str() );
  if( ifile.is_open() ){

    i = 0;
    while( !ifile.eof() ){
      examples << new h_pattern();
      examples[i]->receive_inputs(ifile);
      examples[i]->receive_outputs(ifile);
      i++;
    }
    ifile.close();

    std::cout << "Getting examples from file "<<filename<<" ..."<<std::endl;
    std::cout << examples;
  }
  else{
    std::cout<<"could not open file"<<std::endl;
  }


  //evaluation before learning
  
  std::cout<<std::endl<<"Evaluation of a few examples before learning...."<<std::endl;
  std::cout<<"How many examples at max? ";
  std::cin >> few_examples;
  evaluate_few_examples(net, examples, few_examples);


  //I'm not sure about the way I recon the squared error (stop condition), so I just make it the following way until i get sure

  ans = "y";
  while(ans == "y" || ans =="Y"){

    learning::backpropagation(alpha, net, examples);

    std::cout<<std::endl<<"Evaluation of a few examples after learning...."<<std::endl;
    evaluate_few_examples(net, examples, few_examples);

    std::cout<<"More learnings? y/n _";
    std::cin >> ans;

    if(ans == "y" || ans =="Y"){
      std::cout<<"How many more steps? ";
      std::cin >> N;
      for(i=0; i<N-1; i++)
	learning::backpropagation(alpha, net, examples);
    }
  }

  delete p;
  delete q;

}

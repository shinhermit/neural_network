#include "test_backprop.hpp"

void evaluate_few_examples(network & net, pattern_set & set, int how_many){
  int i, k, set_size, net_size;
  std::vector<float> output;

  set_size = set.size();
  i=0;
  while(i < set_size && i < how_many){

    net << set[i]->inputs();
    net.evaluate();

    std::cout << "Example:" << std::endl;
    std::cout << *set[i];

    std::cout << "Results of hidden layers:"<<std::endl;
    net_size = net.size();
    for(k=0; k < net_size - 1; k++){
      output = net[k]->output();
      std::cout << "[";
      easyContainers::print_vector<float>(output);
      std::cout << "]" << std::endl;
    }

    std::cout << "Output of the network:"<<std::endl;
    output = net.output();
    std::cout << "[";
    easyContainers::print_vector<float>(output);
    std::cout << "]" << std::endl<<std::endl;

    i++;
  }

}

void test_backprop(std::map<std::string,std::string> & args){
  network * p = new heavy_network();
  pattern_set * q = new h_pattern_set();
  std::ifstream ifile;
  std::ofstream ofile;
  int i, layer_size, last, neurons_size, default_input_size, few_examples, N;
  double alpha, default_rate;
  std::string net_file, data_file, default_net_file, default_data_file, layers, ans, save;
  std::istringstream iss;

  network & net = *p;
  pattern_set & examples = *q;

  default_input_size = 3;
  default_rate = 0.5;
  default_data_file = "res/xor";
  default_net_file = "res/network.net";

  //network structure file
  if( args.count("-f") ){
    net_file = args["-f"];
  }
  else{
    net_file = default_net_file;
  }

  if( !args.count("-l") ){
    ifile.open( net_file.c_str() );
    if( ifile.is_open() ){
      net.load(ifile);
      ifile.close();
    }
  }

  //learning data file
  if( args.count("-e") ){
    data_file = args["-e"];
  }
  else{
    data_file = default_data_file;
  }

  //learning rate
  if( args.count("-r") ){
    iss.str(args["-r"]);
    iss >> alpha;
  }
  else{
    alpha = default_rate;
  }

  //the layers
  if( args.count("-l") ){
    layers = args["-l"];
  }
  else{
    layers = "";
  }

  if( layers.size() ){

    iss.clear();
    iss.str(layers);
    while( iss.good() ){
      iss >> layer_size;

      if( iss.good() ){
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
    }

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

  //possible issue: check if file exists (to do)
  ifile.open( data_file.c_str() );
  if( ifile.is_open() ){

    i = 0;
    while( ifile.good() ){
      examples << new h_pattern();
      examples[i]->receive_inputs(ifile);
      examples[i]->receive_outputs(ifile);
      i++;
    }
    ifile.close();

    std::cout << "Getting examples from file "<<data_file<<" ..."<<std::endl;
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
    else{
      std::cout<<"Save? y/n _";
      std::cin >> save;

      if(save == "y" || save == "Y"){
	std::cout << "nom du fichier: res/";
	if(std::cin >> net_file){
	  net_file = "res/"+net_file;
	  ofile.open( net_file.c_str() );
	  if(ofile.is_open() ){
	    net.save(ofile);
	    ofile.close();
	  }
	  else{
	    std::cout << "test_backprop(std::map<std::string,std::string>&) : unable to open save file name"<<std::endl;
	  }
	}
	else{
	  std::cout << "test_backprop(std::map<std::string,std::string>&) : unable to read save file name"<<std::endl;
	}
      }

    }
  }

  delete p;
  delete q;

}

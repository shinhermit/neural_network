#include "dashboard.hpp"

using namespace std;

void usage(){
  cout<<endl<<"Usage:"<<endl;
  cout<<"./dashboard.out [-p program] [-a arguments] [--help]"<<endl;
  cout<<endl<<"--help : show this help"<<endl;

  cout<<endl<<"-p : program to run. Available programs are:"<<endl;

  cout<<endl<<"    unit : the unit utility class for synaptic connections."<<endl;
  cout<<"        -a layer_pos cell_pos"<<endl;

  cout<<endl<<"    synaptic : represents a network synaptic connection."<<endl;
  cout<<"        -a layer_pos1 cell_pos1 layer_pos2 cell_pos2"<<endl;

  cout<<endl<<"    synaptics : a \"set\" of synaptic connections."<<endl;
  cout<<"        -a layer_pos1 cell_pos1 layer_pos2 cell_pos2 ..."<<endl;
  cout<<"          ex: ./dashboard.out -p synaptics -a 0 3 1 1 3 2 2 3 1 4 2 0"<<endl;

  cout<<endl<<"    neuron : formal neuron."<<endl;
  cout<<"        -a num_of_inputs"<<endl;

  cout<<endl<<"    layer : a list of neurons"<<endl;
  cout<<"        -a num_of_neurons num_of_inputs_per_neuron"<<endl;

  cout<<endl<<"    network : generic neural network"<<endl;

  cout<<endl<<"    MLP_model : automate construction of MLP from generic network"<<endl;
  cout<<"        -a layer_size units_size ..."<<endl;
  cout<<"          ex: ./dashboard.out -p MLP_model -a 2 4 3 2 2 3"<<endl;

  cout<<endl<<"    MLP : a specialized network for MLP."<<endl;
  cout<<"        -a num_of_inputs hidden_layer_size"<<endl;
  cout<<"          ex: ./dashboard.out -p MLP -a 3 6"<<endl;

  cout<<endl<<"    pattern : represents a training example (inputs + expected outputs)"<<endl;
  cout<<"        -a data_file"<<endl;

  cout<<endl<<"    pattern_set : a \"set\" of training examples"<<endl;
  cout<<"        -a data_file"<<endl;

  cout<<endl<<"    backpop : train a MLP network with backpropagation"<<endl;
  cout<<"        -a training_data_file learning_rate layer_size,neurons_size..."<<endl;
  cout<<"          ex: ./dashboard.out -p backprop -a res/xor2 0.6 5 2 4 5"<<endl;

  cout << endl;

}

void show_menu(){
  cout<<endl<<"Please, choose a program to run..."<<endl;
  cout<<"[Q]uit"<<endl;
  cout<<"[H]elp"<<endl;
  cout<<"[U]nit class test"<<endl;
  cout<<"[S]ynaptic class test"<<endl;
  cout<<"s[Y]naptics class test"<<endl;
  cout<<"[N]euron class test"<<endl;
  cout<<"[L]ayer class test"<<endl;
  cout<<"n[E]twork class test"<<endl;
  cout<<"[M]LP_model construction test"<<endl;
  cout<<"ML[P] class test"<<endl;
  cout<<"p[A]ttern class test"<<endl;
  cout<<"pa[T]tern set class test"<<endl;
  cout<<"[B]ackprop learning programs from res files"<<endl;
 }

bool parse_cmd_line(int argc, char** argv, string & prog, vector<string> & args){
  int i, k;
  bool allright, goHead;

  allright = true;
  prog = string();
  args = vector<string>();

  if(argc > 1){
    i = 0;
    while(i < argc){

      //unknown option
      if( argv[i][0] == '-' && strcmp(argv[i], "-p") != 0  &&  strcmp(argv[i], "-a") != 0  &&  strcmp(argv[i], "--help") != 0){
	allright = false;
      }

      if( strcmp(argv[i], "--help") == 0 ){
	allright = false; //we want to show usage()
      }

      if( strcmp(argv[i], "-p") == 0 ){
	if(i+1 < argc){
	  if(argv[i+1][0] != '-'){
	    prog = string(argv[i+1]);
	  }
	}
      }

      if( strcmp(argv[i], "-a") == 0){
	k = i + 1;
	goHead = true;
	while(k < argc && goHead){
	  if( argv[k][0] == '-' ){
	    goHead = false;
	  }
	  else{
	    args.push_back( string(argv[k]) );
	  }

	  k++;
	}

      }//end if "-p"

      i++;
    }

  }//end if argc > 1

  return allright;

}

bool apply_choice(string & prog, vector<string> & args){
  bool doWeQuit;

  map<string,int> choice = easyContainers::create_map<string,int>("q",0)("u",1)("unit",1)("s",2)("synaptic",2)("y",3)("synaptics",3)("n",4)("neuron",4)("l",5)("layer",5)("e",6)("network",6)("m",7)("mlp_model",7)("p",8)("mlp",8)("a",9)("pattern",9)("t",10)("pattern_set",10)("b",11)("backprop",11)("h",12)(" ",-1);

  if( !choice.count(prog) ){
    prog = " ";
  }

  doWeQuit = false;

  switch( choice[prog] ){
  case 0:
    cout<<"Goodbye."<<endl;
    doWeQuit = true;
    break;
  case 1:
    test_unit(args);
    break;
  case 2:
    test_synaptic(args);
    break;
  case 3:
    test_synaptics(args);
    break;
  case 4:
    test_neuron(args);
    break;
  case 5:
    test_layer(args);
    break;
  case 6:
    test_network(args);
    break;
  case 7:
    test_MLP_model(args);
    break;
  case 8:
    test_MLP(args);
    break;
  case 9:
    test_pattern(args);
    break;
  case 10:
    test_pattern_set(args);
    break;
  case 11:
    test_backprop(args);
    break;
  case 12:
    usage();
    break;
  default:
    cout<<endl<<"Unknown selection. Please, enter the letter in [] for each option."<<endl<<"For example, enter 'q' to quit"<<endl;
  }

  return doWeQuit;

}

int main(int argc, char** argv){
  string prog;
  vector<string> args;
  bool quit;

  if( !parse_cmd_line(argc, argv, prog, args) ){
    usage();
  }

  if( prog.size() != 0 ){
    quit = apply_choice(prog, args);
  }

  while(!quit){
    show_menu();
    cin >> prog;
    quit = apply_choice(prog, args);
  }

  return 0;
}

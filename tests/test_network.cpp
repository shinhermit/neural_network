#include "test_network.hpp"

void test_network(std::map<std::string,std::string> & args){
  network* p;
  int i;
  std::string filename;
  std::ifstream ifile;
  std::ofstream ofile;

  try{
    std::cout<<std::endl<<std::endl<<"Creating an empty network..."<<std::endl;
    p = new heavy_network();
    network & net = *p;
    std::cout << net;

    std::cout<<std::endl<<std::endl<<"Adding an homogenous input layer of 2 neurons with 3 inputs..."<<std::endl;
    net << new heavy_layer(2, 3);
    net.print();

    std::cout<<std::endl<<std::endl<<"Adding an homogenous layer of 3 neurons with 2 inputs..."<<std::endl;
    net << new heavy_layer(3, 2);
    std::cout << net;

    std::cout<<std::endl<<std::endl<<"Adding an homogenous ouput layer of 2 neurons with 3 inputs"<<std::endl;
    net << new heavy_layer(2, 3);
    std::cout << net;

    std::cout<<std::endl<<std::endl<<"Connecting neurons of layer 2 to neurons of layer 1..."<<std::endl;
    for(i=0; i<3; i++) net.connect(0,0, 1, i);
    for(i=0; i<3; i++) net.connect(0,1, 1, i);
    std::cout << net;

    std::cout<<std::endl<<std::endl<<"Connecting neurons of layer 3 to neurons of layer 2..."<<std::endl;
    for(i=0; i<3; i++) net.connect(1,i, 2, 0);
    for(i=0; i<3; i++) net.connect(1,i, 2, 1);
    std::cout << net;

    std::cout<<std::endl<<std::endl<<"Receiving inputs 2.1, 2.2 and 2.3..."<<std::endl;
    net << 2.1 << 2.2 << 2.3;
    std::cout << net;

    std::cout<<std::endl<<std::endl<<"Evaluating the network..."<<std::endl;
    net.evaluate();
    std::cout << net;

    std::cout<<std::endl<<std::endl<<"Resetting the network..."<<std::endl;
    net.reset();
    std::cout << net;

    std::cout<<std::endl<<std::endl<<"Recurrently connecting neurons of layer 1 to themselves"<<std::endl;
    net.connect(0,0, 0,0);
    net.connect(0,1, 0,1);
    std::cout << net;

    std::cout<<std::endl<<std::endl<<"Receiving values 0.5, 0.6, 0.7..."<<std::endl;
    net << 0.5 << 0.6 << 0.7;
    std::cout << net;

    std::cout<<std::endl<<std::endl<<"Evaluating the network throw time, steps=3..."<<std::endl;
    net.evaluate(3);
    std::cout << net;

    std::cout<<std::endl<<"__________________________________________"<<std::endl;

    std::vector<unit> adjacents;

    std::cout<<std::endl<<std::endl<<"Testing connections methods..."<<std::endl;
    std::cout<<std::endl<<"has_connection( {(0,1)-->(1,1)} ): "<<std::endl;
    std::cout << net.has_connection(0,1, 1,1);

    std::cout<<std::endl<<"has_connection( {(1,1)-->(0,1)} ): "<<std::endl;
    std::cout << net.has_connection(1,1, 0,1);

    std::cout<<std::endl<<"find_connection({(1,0)-->(2,1)}): "<<std::endl;
    std::cout << net.find_connection(1,0, 2,1);

    std::cout<<std::endl<<"disconnect({(1,0)-->(2,1)}): "<<std::endl;
    net.disconnect(1,0, 2,1);
    std::cout << net;

    std::cout<<std::endl<<"connect({(1,0)-->(1,0)})"<<std::endl; //Attention, plus de connection que d'inputs
    net.connect(1,0, 1,0);
    std::cout << net;

    std::cout<<std::endl<<"disconnect_incoming(1,0)"<<std::endl;
    net.disconnect_incoming(1,0);
    std::cout << net;

    std::cout<<std::endl<<"disconnect_outgoing(1,1)"<<std::endl;
    net.disconnect_outgoing(1,1);
    std::cout << net;

    std::cout<<std::endl<<"disconnect_all(1,2)"<<std::endl;
    net.disconnect_all(1,2);
    std::cout << net;

    std::cout<<std::endl<<"succ(0,0)"<<std::endl;
    adjacents = net.succ(0,0);
    std::cout << "[";
    for(i=0; i<(int)adjacents.size(); i++){
      std::cout << adjacents[i];
    }
    std::cout << "]";

    std::cout<<std::endl<<"pred(1,1)"<<std::endl;
    adjacents = net.pred(1,1);
    std::cout << "[";
    for(i=0; i<(int)adjacents.size(); i++){
      std::cout << adjacents[i];
    }
    std::cout << "]"<<std::endl<<std::endl;

    filename = "res/save_network.net";
    std::cout<<std::endl<<std::endl<<"Saving to file "<<filename<<"..."<<std::endl;
    ofile.open( filename.c_str() );
    if( ofile.is_open() ){
      net.save(ofile);
      ofile.close();
    }

    filename = "res/network.net";
    std::cout<<std::endl<<std::endl<<"Loading from file "<<filename<<"..."<<std::endl;
    ifile.open( filename.c_str() );
    if( ifile.is_open() ){
      net.load(ifile);
      ifile.close();
    }
    std::cout << net << std::endl;

    filename = "res/save_network.net";
    std::cout<<std::endl<<std::endl<<"Saving to file "<<filename<<"..."<<std::endl;
    ofile.open( filename.c_str() );
    if( ofile.is_open() ){
      net.save(ofile);
      ofile.close();
    }

  }
  catch(std::string e){
    std::cout << "Caught Exception:"<< std::endl << e << std::endl << std::endl;
  }

  delete p;

}

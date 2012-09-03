#include <iostream>
#include "heavy_network.hpp"

using namespace std;

int main(){
  network* net;
  int i;

  try{
    cout<<endl<<endl<<"Creating an empty network..."<<endl;
    net = new heavy_network();
    cout << net;

    cout<<endl<<endl<<"Adding an homogenous input layer of 2 neurons with 3 inputs..."<<endl;
    *net << new heavy_layer(2, 3);
    net->print();

    cout<<endl<<endl<<"Adding an homogenous layer of 3 neurons with 2 inputs..."<<endl;
    *net << new heavy_layer(3, 2);
    cout << net;

    cout<<endl<<endl<<"Adding an homogenous ouput layer of 2 neurons with 3 inputs"<<endl;
    *net << new heavy_layer(2, 3);
    cout << net;

    cout<<endl<<endl<<"Connecting neurons of layer 2 to neurons of layer 1..."<<endl;
    for(i=0; i<3; i++) net->connect(0,0, 1, i);
    for(i=0; i<3; i++) net->connect(0,1, 1, i);
    cout << net;

    cout<<endl<<endl<<"Connecting neurons of layer 3 to neurons of layer 2..."<<endl;
    for(i=0; i<3; i++) net->connect(1,i, 2, 0);
    for(i=0; i<3; i++) net->connect(1,i, 2, 1);
    cout << net;

    cout<<endl<<endl<<"Receiving inputs 2.1, 2.2 and 2.3..."<<endl;
    *net << 2.1 << 2.2 << 2.3;
    cout << net;

    cout<<endl<<endl<<"Evaluating the network..."<<endl;
    net->evaluate();
    cout << net;

    cout<<endl<<endl<<"Resetting the network..."<<endl;
    net->reset();
    cout << net;

    cout<<endl<<endl<<"Recurrently connecting neurons of layer 1 to themselves"<<endl;
    net->connect(0,0, 0,0);
    net->connect(0,1, 0,1);
    cout << net;

    cout<<endl<<endl<<"Receiving values 0.5, 0.6, 0.7..."<<endl;
    *net << 0.5 << 0.6 << 0.7;
    cout << net;

    cout<<endl<<endl<<"Evaluating the network throw time, steps=3..."<<endl;
    net->evaluate(3);
    cout << net;

    cout<<endl<<"__________________________________________"<<endl;

    vector<unit> adjacents;

    cout<<endl<<endl<<"Testing connections methods..."<<endl;
    cout<<endl<<"has_connection( {(0,1)-->(1,1)} ): "<<endl;
    cout << net->has_connection(0,1, 1,1);

    cout<<endl<<"has_connection( {(1,1)-->(0,1)} ): "<<endl;
    cout << net->has_connection(1,1, 0,1);

    cout<<endl<<"find_connection({(1,0)-->(2,1)}): "<<endl;
    cout << net->find_connection(1,0, 2,1);

    cout<<endl<<"disconnect({(1,0)-->(2,1)}): "<<endl;
    net->disconnect(1,0, 2,1);
    cout << net;

    cout<<endl<<"connect({(1,0)-->(1,0)})"<<endl; //Attention, plus de connection que d'inputs
    net->connect(1,0, 1,0);
    cout << net;

    cout<<endl<<"disconnect_incoming(1,0)"<<endl;
    net->disconnect_incoming(1,0);
    cout << net;

    cout<<endl<<"disconnect_outgoing(1,1)"<<endl;
    net->disconnect_outgoing(1,1);
    cout << net;

    cout<<endl<<"disconnect_all(1,2)"<<endl;
    net->disconnect_all(1,2);
    cout << net;

    cout<<endl<<"succ(0,0)"<<endl;
    adjacents = net->succ(0,0);
    cout << "[";
    for(i=0; i<(int)adjacents.size(); i++){
      cout << adjacents[i];
    }
    cout << "]";

    cout<<endl<<"pred(1,1)"<<endl;
    adjacents = net->pred(1,1);
    cout << "[";
    for(i=0; i<(int)adjacents.size(); i++){
      cout << adjacents[i];
    }
    cout << "]"<<endl<<endl;
  }
  catch(std::string e){
    cout << "Caught Exception:"<< endl << e << endl << endl;
  }

  delete net;

  return 0;
}

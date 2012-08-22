#include <iostream>
#include "network.hpp"

using namespace std;

int main(){
  network net;
  int i;

  try{
    cout<<endl<<endl<<"Creating an empty network..."<<endl;
    net.print();

    cout<<endl<<endl<<"Adding an homogenous input layer of 2 neurons with 3 inputs..."<<endl;
    net << perceptron(2, 3);
    net >> cout;

    cout<<endl<<endl<<"Adding an homogenous layer of 3 neurons with 2 inputs..."<<endl;
    net << perceptron(3, 3);
    net >> cout;

    cout<<endl<<endl<<"Adding an homogenous ouput layer of 2 neurons with 3 inputs"<<endl;
    net << perceptron(2, 3);
    net >> cout;

    cout<<endl<<endl<<"Connecting neurons of layer 2 to neurons of layer 1..."<<endl;
    for(i=0; i<3; i++) net.connect(0,0, 1, i);
    for(i=0; i<3; i++) net.connect(0,1, 1, i);
    net >> cout;

    cout<<endl<<endl<<"Connecting neurons of layer 3 to neurons of layer 2..."<<endl;
    for(i=0; i<3; i++) net.connect(1,i, 2, 0);
    for(i=0; i<3; i++) net.connect(1,i, 2, 1);
    net >> cout;

    cout<<endl<<endl<<"Receiving inputs 2.1, 2.2 and 2.3..."<<endl;
    net << 2.1 << 2.2 << 2.3;
    net >> cout;

    cout<<endl<<endl<<"Evaluating the neuron..."<<endl;
    net.evaluate();
    net >> cout;

    cout<<endl<<endl<<"Resetting the network..."<<endl;
    net.reset();
    net>>cout;

    cout<<endl<<endl<<"Recurrently connecting neurons of layer 1 to themselves"<<endl;
    net.connect(0,0, 0,0);
    net.connect(1,1, 1,1);
    net >> cout;

    cout<<endl<<endl<<"Receiving values 0.5, 0.6, 0.7..."<<endl;
    net << 0.5 << 0.6 << 0.7;
    net >> cout;

    cout<<endl<<endl<<"Evaluating the network throw time, steps=3..."<<endl;
    net.evaluate(3);
    net >> cout;

    cout<<endl<<"__________________________________________"<<endl;

    vector<unit> adjacents;

    cout<<endl<<endl<<"Testing connections methods..."<<endl;
    cout<<endl<<"are_connected(0,1, 1,1): "<<endl;
    cout << net.are_connected(0,1, 1,1);

    cout<<endl<<"are_connected(1,1, 0,1): "<<endl;
    cout << net.are_connected(1,1, 0,1);

    cout<<endl<<"registered_connection({(0,1), (1,1)}): "<<endl;
    cout << net.registered_connection(0,1, 1,1);

    cout<<endl<<"registered_connection({(1,1), (0,1)}): "<<endl;
    cout << net.registered_connection(1,1, 0,1);

    cout<<endl<<"find_connection({(1,0)-->(2,1)}): "<<endl;
    cout << net.find_connection(1,0, 2,1);

    cout<<endl<<"disconnect({(1,0)-->(2,1)}): "<<endl;
    net.disconnect(1,0, 2,1);
    net >> cout;

    cout<<endl<<"connect({(1,0)-->(1,0)})"<<endl;
    net.connect(1,0, 1,0);
    net >> cout;

    cout<<endl<<"disconnect_incoming(1,0)"<<endl;
    net.disconnect_incoming(1,0);
    net >> cout;

    cout<<endl<<"succ(0,0)"<<endl;
    adjacents = net.succ(0,0);
    cout << "[";
    for(i=0; i<(int)adjacents.size(); i++){
      cout << adjacents[i];
    }
    cout << "]";

    cout<<endl<<"pred(1,1)"<<endl;
    adjacents = net.pred(1,1);
    cout << "[";
    for(i=0; i<(int)adjacents.size(); i++){
      cout << adjacents[i];
    }
    cout << "]";
  }
  catch(std::string e){
    cout << e;
  }

  return 0;
}

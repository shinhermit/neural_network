#include <iostream>
#include "synaptic.hpp"

using namespace std;

int main(){
  int i, layer, position;
  unit src, dst;
  synaptic synapses[3];

  //asking data for 3 connections to the user
  cout<<endl<<"Creation of 3 connections..."<<endl;
  for(i=0; i<3; i++){
    cout<<"connection "<<i+1<<endl;

    cout<<"layer where the source unit is: ";
    cin>>layer;
    cout<<"position in the layer: ";
    cin>>position;
    src = unit(layer, position);

    cout<<"layer where the destination unit is: ";
    cin>>layer;
    cout<<"position in the layer: ";
    cin>>position;
    dst = unit(layer, position);

    synapses[i] = synaptic(src, dst);
  }

  cout<<endl<<"Comparing the connections..."<<endl;
  cout<<"synapse1 == synapse2 : ";
  if(synapses[0] == synapses[1])
    cout<<"true"<<endl;
  else
    cout<<"false"<<endl;

  cout<<"synapse1 < synapse3 : ";
  if(synapses[0] < synapses[2])
    cout<<"true"<<endl;
  else
    cout<<"false"<<endl;

  cout<<"synapse2 <= synapse3 : ";
  if(synapses[1] <= synapses[2])
    cout<<"true"<<endl;
  else
    cout<<"false"<<endl;

  cout<<endl<<"printing synapses ..."<<endl;
  cout<<"1: "<<synapses[0]<<endl;
  cout<<"2: "<<synapses[1]<<endl;
  cout<<"3: "<<synapses[2]<<endl;

  cout<<endl<<"unsing layer(), source() and dest() observers ..."<<endl;
  cout<<"1: layer() -> "<<synapses[0].layer()<<" | source() -> "<<synapses[0].source()<<" | dest() -> "<<synapses[0].dest()<<endl;

  return 0;
}

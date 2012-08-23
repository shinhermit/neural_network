#include <iostream>
#include "unit.hpp"

using namespace std;

int main(){
  int i, layer, position;
  unit units[3];

  //asking data for 3 units to the user
  cout<<endl<<"Creation of 3 units..."<<endl;
  for(i=0; i<3; i++){
    cout<<"layer where the unit "<<i+1<<" is: ";
    cin>>layer;
    cout<<"position in the layer: ";
    cin>>position;
    units[i] = unit(layer,position);
  }

  cout<<endl<<"Comparing the units..."<<endl;
  cout<<"unit1 == unit2 : ";
  if(units[0] == units[1])
    cout<<"true"<<endl;
  else
    cout<<"false"<<endl;

  cout<<"unit1 == unit3 : ";
  if(units[0] == units[2])
    cout<<"true"<<endl;
  else
    cout<<"false"<<endl;

  cout<<"unit2 == unit3 : ";
  if(units[1] == units[2])
    cout<<"true"<<endl;
  else
    cout<<"false"<<endl;

  cout<<endl<<"printing units ..."<<endl;
  cout<<"1: "; units[0].print(); cout<<endl;
  cout<<"2: "<<units[1]<<endl;
  cout<<"3: "<<units[2]<<endl;

  cout<<endl<<"unsing layer() and pos() observers ..."<<endl;
  cout<<"1: layer() -> "<<units[0].layer()<<" | pos() -> "<<units[0].pos()<<endl;

  return 0;
}

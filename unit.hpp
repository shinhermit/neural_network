/**
 *@file unit.hpp
 *@brief basic brick neural synaptic connections
 *@version 0.1
 *@author Josuah ARON
 *@date 19 august 2012
 *
 */

#ifndef UNIT_HPP
#define UNIT_HPP

#include <cstdlib>
#include <iostream>

/**
 *@class unit
 *@brief identifies a cell in a network
 *a cell is a neuron in a neural network
 *a unit object identifies a cell by a couple of data (layer index, neuron index)
 *it uses less space than an actual neuron and is used in synatic connections
 *layer index is the position of the layer of the cell in the network
 *neuron index is the position of the cell in the layer
 *a layer is actually a perceptron.
 */
class unit
{
private:
  int _layer; /*!< cell's layer indice*/
  int _pos; /*!< cell's position in layer*/

public:
  /**
   *@brief constructor
   *@param layer parent layer indice
   *@param pos position in the parent layer
   */
  unit(int=0, int=0);

  /**
   *@brief copy constructor
   */
  unit(const unit &);

  /**
   *@brief destructor
   */
  ~unit();

  /**
   *@brief operator =
   */
  unit & operator=(const unit &);

  /**
   *@brief operator >>
   */
  unit & operator>>(std::ostream&);

  /**
   *@brief operator <<
   *just to keep cout style
   */
  friend std::ostream & operator<<(std::ostream&, unit&);

  /**
   *@brief operator ==
   *@return true when the layers indices and neurons postions recpectivly match
   */
  friend bool operator==(const unit&, const unit&);


  /**
   *@brief accessor
   *@return indice of the layer where the unit is
   */
  int layer()const;

  /**
   *@brief accessor
   *@param postion of the unit in it's layer
   */
  int pos()const;

  /**
   *@brief prints the current state of the object
   *useful for testing
   */
  void print();
};

#endif









/**
 *@section Example
 *@code
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
  cout<<"2: "; units[1].print(); cout<<endl;
  cout<<"3: "<<units[2]<<endl;

  cout<<endl<<"unsing layer() and pos() observers ..."<<endl;
  cout<<"1: layer() -> "<<units[0].layer()<<" | pos() -> "<<units[0].pos()<<endl;

  return 0;
}
 *@endcode
 */

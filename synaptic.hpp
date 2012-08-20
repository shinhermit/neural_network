/**
 *@file synaptic.hpp
 *@brief formal neural network connection
 *@version 0.1
 *@author Josuah Aron
 *@date 19 August 2012
 *
 */

#ifndef SYNAPTIC_HPP
#define SYNAPTIC_HPP

#include "unit.hpp"

/**
 *@class synaptic
 *@brief represents a connection between 2 neurons
 *
 *This class uses the class unit, that identifies a neural cell in a network (an occupies less space)
 *It represents a connection by a couple of objects unit, as (src, dst) = (outputing, inputing)
 */
class synaptic
{
private:
  unit _src; /*!< the outputing unit*/
  unit _dst; /*!< the inputing unit*/

public:
  /**
   *@brief default constructor
   */
  synaptic();

  /**
   *@brief constructor
   *@param source outputing unit
   *@param destination inputing unit
   */
  synaptic(unit, unit);

  /**
   *@brief copy constructor
   */
  synaptic(const synaptic&);

  /**
   *@brief destructor
   */
  ~synaptic();

  /**
   *@brief operator =
   */
  synaptic & operator=(const synaptic&);

  /**
   *@brief operator <<
   */
  friend std::ostream & operator<<(std::ostream&, const synaptic&);

  /**
   *@brief operator ==
   *@return true if the synapses both link the same units in the same direction
   */
  friend bool operator==(const synaptic&, const synaptic&);


  /**
   *@brief accessor
   *return the layer in which the synaptic connection must be registerd (inputing unit's layer)
   *@return indice of the registration layer in the network
   */
  int layer()const;

  /**
   *@brief accessor
   *@return reference of the outputing unit
   */
  unit & source();

  /**
   *@brief accessor
   *@return reference of inputing unit
   */
  unit & dest();
};

#endif








/**
 *@section Example
@code
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

  cout<<"synapse1 == synapse3 : ";
  if(synapses[0] == synapses[2])
    cout<<"true"<<endl;
  else
    cout<<"false"<<endl;

  cout<<"synapse2 == synapse3 : ";
  if(synapses[1] == synapses[2])
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
@endcode
 */

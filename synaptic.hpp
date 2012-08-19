/**
 *@file synaptic.hpp
 *@brief formal neural network connection
 *@author Josuah Aron
 *@date 19 August 2012
 *
 */

#ifndef SYNAPTIC_HPP
#define SYNAPTIC_HPP

#include <iostream>
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

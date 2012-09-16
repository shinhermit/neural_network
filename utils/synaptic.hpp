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

#include <sstream>
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
   *@brief constructor
   *@param src_layer layer of the source outputing unit
   *@param src_pos position of the source outputing unit
   *@param dst_layer of the destination inputing unit
   *@param dst_pos position of the destination inputing unit
   */
  synaptic(int,int, int,int);

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
   *@brief operator >>
   */
  synaptic & operator>>(std::ostream&);

  /**
   *@brief operator <<
    *Just to keep std::cout << x style
   */
  friend std::ostream & operator<<(std::ostream&, synaptic&);

  /**
   *@brief operator ==
   *@return true if the synapses both link the same units in the same direction
   */
  friend bool operator==(const synaptic&, const synaptic&);

  /**
   *@brief operator !=
   *@return true when the layers indices and neurons postions recpectivly match
   */
  friend bool operator!=(const synaptic&, const synaptic&);

  /**
   *@brief operator <
   *@return true when the layers indices and neurons postions recpectivly match
   */
  friend bool operator<(const synaptic&, const synaptic&);

  /**
   *@brief operator >
   *@return true when the layers indices and neurons postions recpectivly match
   */
  friend bool operator>(const synaptic&, const synaptic&);

  /**
   *@brief operator <=
   *@return true when the layers indices and neurons postions recpectivly match
   */
  friend bool operator<=(const synaptic&, const synaptic&);

  /**
   *@brief operator >=
   *@return true when the layers indices and neurons postions recpectivly match
   */
  friend bool operator>=(const synaptic&, const synaptic&);


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

  /**
   *@brief writes the state of the neuron to a file (any output stream actually)
   */
  void save(std::ostream&);

  /**
   *@brief loads the state of the neuron from a file (any input stream actually)
   */
  void load(std::istream&);

  /**
   *@brief prints the current state of the neuron
   *useful for testing
   */
  void print();
};

#endif

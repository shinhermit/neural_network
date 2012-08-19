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
};

#endif

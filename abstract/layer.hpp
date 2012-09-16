/**
 *@file layer.hpp
 *@brief defining the compulsory interface of a layer.
 *@author Josuah ARON
 *@version 0.1
 *@date 01 September 2012
 *
 */

#ifndef LAYER_HPP
#define LAYER_HPP

#include "neuron.hpp"

/**
 *@class layer
 *@brief a group of neurons
 *We attend to define two kinds of layers, one with internal data (id_layer) and one with data in a database (db_layer).
 *These classes will be used with the same algorithms, so the abstract class is designed for polymorphism
 *
 */
class layer
{
public:
  /**
   *@brief default constructor
   */
  layer();

  /**
   *@brief constructor
   *creates an homogenous layer ie in wich all neurons have the same number of inputs
   *@param size number of neurons of the layer
   *@param neuron_size size of neurons ie number of inputs of the neurons
   */
  layer(int, int=1);

  /**
   *@brief copy constructor
   */
  layer(const layer&);

  /**
   *@brief destructor
   */
  virtual ~layer();

  /**
   *@brief operator =
   */
  virtual layer & operator=(layer&)=0;

  /**
   *@brief operator []
   *accesses a neuron of the layer
   *@param index position of the neuron in the layer
   *@return pointer the neuron (polymorphic)
   */
  virtual neuron * operator[](int)=0;

  /**
   *@brief operator >>
   */
  virtual layer & operator>>(std::ostream&)=0;

  /**
   *@brief operator ostream << layer*
   */
  friend std::ostream & operator<<(std::ostream&, layer&);

  /**
   *@brief operator <<
   *equivalent to layer::receive(double)
   */
  virtual layer & operator<<(double)=0;

  /**
   *@brief operator <<
   *equivalent to layer::receive(std::vector<double>&)
   */
  virtual layer & operator<<(const std::vector<double>&)=0;

  /**
   *@brief operator <<
   *adds a neuron at the end of the layer
   */
  virtual layer & operator<<(neuron*)=0;


  /**
   *@brief size of the layer
   *@return number of neurons of the layer
   */
  virtual int size()const=0;

  /**
   *@brief changes the size of the layer
   *usefull to remove at once the last neurons of the layer
   *@param size new size
   */
  virtual void resize(int=1)=0;

  /**
   *@brief inserts a neuron in the layer
   *@param cell new neuron to add
   *@param pos where we want to add the neuron in the layer
   */
  virtual void add(neuron*, int=-1)=0;

  /**
   *@brief removes a neuron from the layer
   *@param index position of the neuron in the layer
   */
  virtual void remove(int)=0;


  /**
   *@brief sets random weights for all the neurons
   *Actually, simply spreads the neuron::rnd_weights() throw all the neurons of the layer
   *@param min min weight value
   *@param max max weight value
   */
  virtual void rnd_weights(double=-0.5, double=0.5)=0;

  /**
   *@brief receives a single input
   *the layer spreads the value to all it's neurons
   *@param value value of the input
   */
  virtual void receive(double)=0;

  /**
   *@brief receives multiple values
   *@param data values to receive
   */
  virtual void receive(std::vector<double>)=0;

  /**
   *@brief processes the data
   */
  virtual void evaluate()=0;

  /**
   *@brief result of the treatment
   *@return vector of the ouputs of the neurons of the layer
   */
  virtual std::vector<float> output()=0;

  /**
   *@brief resets neuron
   *does not reset weights (use rnd_weights() method)
   */
  virtual void reset()=0;

  /**
   *@brief writes the state of the neuron to a file (any output stream actually)
   */
  virtual void save(std::ostream&)=0;

  /**
   *@brief loads the state of the neuron from a file (any input stream actually)
   */
  virtual void load(std::istream&)=0;


  /**
   *@brief prints the current state of the neuron
   *useful for testing
   */
  virtual void print()=0;
};

#endif

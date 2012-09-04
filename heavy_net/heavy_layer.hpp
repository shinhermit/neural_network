/**
 *@file heavy_layer.hpp
 *@brief defining the heavy_layer.
 *@author Josuah ARON
 *@version 0.2
 *@date 19 August 2012
 *
 */

#ifndef HEAVY_LAYER_HPP
#define HEAVY_LAYER_HPP

#include "heavy_neuron.hpp"
#include "layer.hpp"

/**
 *@class heavy_layer
 *@brief a group of neurons
 *
 *we choose direct access because we don't need fast modifications of the structure, but fast processings
 *we don't say at first which criteria groups some neurons into a heavy_layer, evenif it's generally admitted that neuron's in a heavy_layer have no link to each others.
 *Our architecture actually allows any link between neurons, so the criteria can be different.
 *The heavy_layer can receive the information value after value or as a vector
 *it gives it's output as a vector.
 */
class heavy_layer : public layer
{
private:
  std::vector<neuron*> _neurons; /*!< heavy_neurons of the heavy_layer*/

  void _deep_copy(const heavy_layer&);

  void _deep_clear();

public:
  /**
   *@brief default constructor
   */
  heavy_layer();

  /**
   *@brief constructor
   *creates an homogenous heavy_layer ie in wich all heavy_neurons have the same number of inputs
   *@param size number of heavy_neurons of the heavy_layer
   *@param heavy_neuron_size size of heavy_neurons ie number of inputs of the heavy_neurons
   */
  heavy_layer(int, int=1);

  /**
   *@brief copy constructor
   */
  heavy_layer(const heavy_layer&);

  /**
   *@brief destructor
   */
  ~heavy_layer();

  /**
   *@brief operator =
   */
  heavy_layer & operator=(const heavy_layer&);

  /**
   *@brief operator =
   */
  heavy_layer & operator=(layer&);

  /**
   *@brief operator []
   *accesses a heavy_neuron of the heavy_layer
   *@param index position of the heavy_neuron in the heavy_layer
   *@return reference of the heavy_neuron
   */
  neuron * operator[](int);

  /**
   *@brief operator >>
   */
  heavy_layer & operator>>(std::ostream&);

  /**
   *@brief operator <<
   *just to keep std::cout << x style
   */
  friend std::ostream & operator<<(std::ostream&, heavy_layer&);

  /**
   *@brief operator <<
   *equivalent to heavy_layer::receive(double)
   */
  heavy_layer & operator<<(double);

  /**
   *@brief operator <<
   *equivalent to heavy_layer::receive(std::vector<double>&)
   */
  heavy_layer & operator<<(const std::vector<double>&);

  /**
   *@brief operator <<
   *adds a heavy_neuron at the end of the heavy_layer
   */
  heavy_layer & operator<<(neuron*);


  /**
   *@brief size of the heavy_layer
   *@return number of heavy_neurons of the heavy_layer
   */
  int size()const;

  /**
   *@brief changes the size of the heavy_layer
   *usefull to remove at once the last heavy_neurons of the heavy_layer
   *@param size new size
   */
  void resize(int=1);

  /**
   *@brief inserts a heavy_neuron in the heavy_layer
   *@param cell new heavy_neuron to add
   *@param pos where we want to add the heavy_neuron in the heavy_layer
   */
  void add(neuron*, int=-1);

  /**
   *@brief removes a heavy_neuron from the heavy_layer
   *@param index position of the heavy_neuron in the heavy_layer
   */
  void remove(int);


  /**
   *@brief sets random weights for all the heavy_neurons
   *Actually, simply spreads the heavy_neuron::rnd_weights() throw all the heavy_neurons of the heavy_layer
   *@param min min weight value
   *@param max max weight value
   */
  void rnd_weights(double=-0.5, double=0.5);

  /**
   *@brief receives a single input
   *the heavy_layer spreads the value to all it's heavy_neurons
   *@param value value of the input
   */
  void receive(double);

  /**
   *@brief receives multiple values
   *@param data values to receive
   */
  void receive(std::vector<double>);

  /**
   *@brief processes the data
   */
  void evaluate();

  /**
   *@brief result of the treatment
   *@return vector of the ouputs of the heavy_neurons of the heavy_layer
   */
  std::vector<float> output();

  /**
   *@brief resets heavy_neuron
   *does not reset weights (use rnd_weights() method)
   */
  void reset();


  /**
   *@brief prints the current state of the heavy_neuron
   *useful for testing
   */
  void print();
};

#endif

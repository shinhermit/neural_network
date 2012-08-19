/**
 *@file perceptron.hpp
 *@brief defining the perceptron.
 *@author Josuah ARON
 *@version 0.1
 *@date 19 August 2012
 *
 */

#ifndef PERCEPTRON_HPP
#define PERCEPTRON_HPP

#include "neuron.hpp"

/**
 *@class perceptron
 *@brief a group of neurons
 *
 *we choose direct access because we don't need fast modifications of the structure, but fast processings
 *we don't say at first which criteria groups some neurons into a perceptron, evenif it's generally admitted that neuron's in a perceptron have no link to each others.
 *Our architecture actually allows any link between neurons, so the criteria can be different.
 *The perceptron can receive the information value after value or as a vector
 *it gives it's output as a vector.
 */
class perceptron
{
private:
  std::vector<neuron> _neurons; /*!< neurons of the perceptron*/

public:
  /**
   *@brief default constructor
   */
  perceptron();

  /**
   *@brief constructor
   *creates an homogenous perceptron ie in wich all neurons have the same number of inputs
   *@param size number of neurons of the perceptron
   *@param neuron_size size of neurons ie number of inputs of the neurons
   */
  perceptron(int, int=1);

  /**
   *@brief copy constructor
   */
  perceptron(const perceptron&);

  /**
   *@brief destructor
   */
  ~perceptron();

  /**
   *@brief operator =
   */
  perceptron & operator=(const perceptron&);

  /**
   *@brief operator []
   *accesses a neuron of the perceptron
   *@param index position of the neuron in the perceptron
   *@return reference of the neuron
   */
  neuron & operator[](int);


  /**
   *@brief size of the perceptron
   *@return number of neurons of the perceptron
   */
  int size()const;

  /**
   *@brief changes the size of the perceptron
   *usefull to remove at once the last neurons of the perceptron
   *@param size new size
   */
  void resize(int=1);

  /**
   *@brief adds a neuron in the perceptron
   *@param cell new neuron to add
   *@param position of the added neuron in the perceptron
   */
  int add(neuron);

  /**
   *@brief removes a neuron from the perceptron
   *@param index position of the neuron in the perceptron
   */
  void remove(int);


  /**
   *@brief sets random weights for all the neurons
   *Actually, simply spreads the neuron::rnd_weights() throw all the neurons of the perceptron
   *@param min min weight value
   *@param max max weight value
   */
  void rnd_weights(double=-0.5, double=0.5);

  /**
   *@brief receives a single input
   *the perceptron spreads the value to all it's neurons
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
   *@return vector of the ouputs of the neurons of the perceptron
   */
  std::vector<float> output();

  /**
   *@brief resets neuron
   *does not reset weights (use rnd_weights() method)
   */
  void reset();
};

#endif

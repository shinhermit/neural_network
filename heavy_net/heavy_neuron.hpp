/**
 *@file heavy_neuron.hpp
 *@brief base element of heavy neural networks.
 *@author Josuah ARON
 *@version 0.1
 *@date 19 August 2012
 *
 */

#ifndef HEAVY_NEURON_HPP
#define HEAVY_NEURON_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "neuron.hpp"

/**
 *@class heavy_neuron
 *@brief represents a formal heavy neuron
 *A heavy neuron is a neuron object that has its data in the RAM, as opposed to light neurons, which have their data in a database.
 *the inputs of the heavy_neuron are represented by it's table of weights.
 *It has an index that points the next input to be received.
 *The inputs are weighted and add to an accumulator before the evaluation of the weighted sum by the activation function.
 *the activation function is the sigmoid function.
 */
class heavy_neuron : public neuron
{
private:
  int _size; /*!< number of inputs*/

  std::vector<double> _weights; /*!< table of the weights. Indice 0 is the biais*/

  int _index; /*!< currently indexed input (and weights)*/

  double _buffer; /*!< weighted sum accumulator*/

  float _output; /*!< last evaluated output */

  static bool _seeded; /*!< call srand(time(NULL)) only once*/

public:
  /**
   *@brief allows the program to know if class neuron has seed srand()
   *@return true if class neuron has call srand(), false is not
   */
  static bool seeded();

  /**
   *@brief default constructor
   *@param size number of inputs of the heavy_neuron
   */
  heavy_neuron(int=neurals::MIN_INPUTS);

  /**
   *@brief copy constructor
   */
  heavy_neuron(const heavy_neuron &);

  /**
   *@brief destructor
   */
  ~heavy_neuron();

  /**
   *@brief operator =
   */
  heavy_neuron & operator=(const heavy_neuron &);

  /**
   *@brief operator =
   */
  heavy_neuron & operator=(neuron &);

  /**
   *@brief operator >>
   */
  heavy_neuron & operator>>(std::ostream&);

  /**
   *@brief operator <<
   *just to keep std::cout << x style
   */
  friend std::ostream & operator<<(std::ostream&, heavy_neuron&);

  /**
   *@brief operator <<
   *equivalent to heavy_neuron::receive(double)
   */
  heavy_neuron & operator<<(double);

  /**
   *@brief operator <<
   *equivalent to heavy_neuron::receive(std::vector<double>&)
   */
  heavy_neuron & operator<<(const std::vector<double>&);

  /**
   *@brief randomly sets the weights
   *@param  min weight value
   *@param  max weight value
   */
  void rnd_weights(double=neurals::RND_MIN, double=neurals::RND_MAX);

  /**
   *@brief receives a new input
   *multiplies the input by it's weight and adds it to the accumulator
   *@param value the actual input
   */
  void receive(double);

  /**
   *@brief receives multiple inputs
   *@param data vector of inputs
   */
  void receive(const std::vector<double>&);

  /**
   *@brief gives the output of the unit.
   *@return result of the treatment by the unit
   */
  float evaluate();

  /**
   *@brief tell is heavy_neuron is active or not
   *@return true if output > 0.5, false if not
   */
  bool is_active()const;

  /**
   *@brief accesses the input index value
   *@return position of the index
   */
  int input_index()const;

  /**
   *@brief returns the number of inputs of the heavy_neuron
   *@return size of the heavy_neuron
   */
  int size()const;

  /**
   *@brief resets the accumulator and the output
   */
  void reset();

  /**
   *@brief modifies the number of inputs of the heavy_neuron
   *@param new_size the new size
   *@param min weight value for eventually new inputs
   *@param max weight value for eventually new inputs
   */
  void resize(int=1, double=neurals::RND_MIN, double=neurals::RND_MIN);

  /**
   *@brief returns the last avaluated output
   *@return last processing result
   */
  double getBuffer()const;

  /**
   *@brief returns the last avaluated output
   *@return last processing result
   */
  float output()const;

  /**
   *@brief returns only 0 or 1
   *Useful to create binary heavy_neurons (like in Hopfield architecture)
   *@return last processing result
   */
  short binary_output()const;

  /**
   *@brief the i-th weight of the heavy_neuron
   *@param pos index of the weight
   *@return value of the weight
   */
  std::vector<double> weights();

  /**
   *@brief the i-th weight of the heavy_neuron
   *@param pos index of the weight
   *@return value of the weight
   */
  double getWeight(int);

  /**
   *@brief sets a value for a weight
   *This method is useful to train the heavy_neuron (fine tunning the weights)
   *@param pos index of the weight
   *@param value new value
   */
  void setWeight(int, double);

  /**
   *@brief prints the current state of the heavy_neuron
   *useful for testing
   */
  void print();
};

#endif

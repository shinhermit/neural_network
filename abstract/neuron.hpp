/**
 *@file neuron.hpp
 *@brief interface for neuron classes.
 *@author Josuah ARON
 *@version 0.1
 *@date 01 September 2012
 *
 */

#ifndef NEURON_HPP
#define NEURON_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "neurals.hpp"

/**
 *@class neuron
 *@brief compulsory interface for our formal neurons
 *We attend to design tow classes of ANN: one with inner data, and one with data in a database.
 *In the second case (outer data), the idea is that we always have enough memory for an object neuron, and there will always be only one neuron in the RAM at an instant.
 */
class neuron
{
protected:
  /**
   *@brief neural activation fonction
   *We use the sigmoide function: g(x)= 1/(1+exp(-x))
   *@param buffered weighted sum of the inputs
   *@return float result of the sigmoide function calculus.
   */
  float _activation(double);

public:
  /**
   *@brief default constructor
   *@param size number of inputs of the neuron
   */
  neuron(int=neurals::MIN_INPUTS);

  /**
   *@brief copy constructor
   */
  neuron(const neuron &);

  /**
   *@brief destructor
   */
  virtual ~neuron();

  /**
   *@brief operator =
   */
  virtual neuron & operator=(neuron&)=0;

  /**
   *@brief operator >>
   */
  virtual neuron & operator>>(std::ostream&)=0;

  /**
   *@brief operator <<
   *make it easy for polimorphism (pointers)
   */
  friend std::ostream & operator<<(std::ostream&, neuron&);

  /**
   *@brief operator <<
   *equivalent to neuron::receive(double)
   */
  virtual neuron & operator<<(double)=0;

  /**
   *@brief operator <<
   *equivalent to neuron::receive(std::vector<double>&)
   */
  virtual neuron & operator<<(const std::vector<double>&)=0;

  /**
   *@brief randomly sets the weights
   *@param  min weight value
   *@param  max weight value
   */
  virtual void rnd_weights(double=neurals::RND_MIN, double=neurals::RND_MAX)=0;

  /**
   *@brief receives a new input
   *multiplies the input by it's weight and adds it to the accumulator
   *@param value the actual input
   */
  virtual void receive(double)=0;

  /**
   *@brief receives multiple inputs
   *@param data vector of inputs
   */
  virtual void receive(const std::vector<double>&)=0;

  /**
   *@brief gives the output of the unit.
   *@return result of the treatment by the unit
   */
  virtual float evaluate()=0;

  /**
   *@brief tell is neuron is active or not
   *@return true if output > 0.5, false if not
   */
  virtual bool is_active()const=0;

  /**
   *@brief accesses the input index value
   *@return position of the index
   */
  virtual int input_index()const=0;

  /**
   *@brief returns the number of inputs of the neuron
   *@return size of the neuron
   */
  virtual int size()const=0;

  /**
   *@brief resets the accumulator and the output
   */
  virtual void reset()=0;

  /**
   *@brief modifies the number of inputs of the neuron
   *@param new_size the new size
   *@param min weight value for eventually new inputs
   *@param max weight value for eventually new inputs
   */
  virtual void resize(int=1, double=neurals::RND_MIN, double=neurals::RND_MIN)=0;

  /**
   *@brief returns the last avaluated output
   *@return last processing result
   */
  virtual double getBuffer()const=0;

  /**
   *@brief returns the last avaluated output
   *@return last processing result
   */
  virtual float output()const=0;

  /**
   *@brief returns only 0 or 1
   *Useful to create binary neurons (like in Hopfield architecture)
   *@return last processing result
   */
  virtual short binary_output()const=0;

  /**
   *@brief the i-th weight of the neuron
   *@param pos index of the weight
   *@return value of the weight
   */
  virtual double getWeight(int)=0;


  /**
   *@brief the i-th weight of the neuron
   *@param pos index of the weight
   *@return value of the weight
   */
  virtual std::vector<double> weights()=0;

  /**
   *@brief sets a value for a weight
   *This method is useful to train the neuron (fine tunning the weights)
   *@param pos index of the weight
   *@param value new value
   */
  virtual void setWeight(int, double)=0;

  /**
   *@brief prints the current state of the neuron
   *useful for testing
   */
  virtual void print()=0;
};

#endif

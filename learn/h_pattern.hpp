/**
 *@file h_pattern.hpp
 *@brief a class designed for naural networs learning algorothms
 *@version 0.1
 *@author Josuah Aron
 *@date 03 September August 2012
 *
 */
#ifndef H_PATTERN_HPP
#define H_PATTERN_HPP

#include "pattern.hpp"

/**
 *@class h_pattern
 *@brief heavy h_pattern. designed for learning algorithms
 *make the manipulation of learning examples easier
 *represents a couple (input data, expected ouputs)
 *
 */
class h_pattern : public pattern
{
public:
  /**
   *@brief default constructor
   */
  h_pattern();

  /**
   *@brief copy constructor
   */
  h_pattern(const h_pattern&);

  /**
   *@brief destructor
   */
  ~h_pattern();

  /**
   *@brief operator =
   */
  h_pattern & operator=(const h_pattern&);

  /**
   *@brief operator =
   */
  h_pattern & operator=(const pattern&);

  /**
   *@brief operator h_pattern >> ostream
   */
  h_pattern & operator>>(std::ostream&);

  /**
   *@brief operator ostream << h_pattern
   */
  friend std::ostream & operator<<(std::ostream&, h_pattern&);

  /**
   *@brief operator pattern<<double
   *easily receives an input for the example
   */
  h_pattern & operator<<(double);

  /**
   *@brief operator pattern(double)
   *easily receives an expected output for the example
   */
  h_pattern & operator()(float);

  /**
   *@brief the number of input data values
   *@return the number of input values
   */
  int inputs_size();

  /**
   *@brief number of output data values
   *@return the number of output values
   */
  int outputs_size();

  /**
   *@brief receives (stores) a value as an input
   *@param value value to store
   */
  h_pattern & receive_input(double);

  /**
   *@brief receives (stores) a value as an expected output
   *@param value the expected result component to store
   */
  h_pattern & receive_ouput(float);

  /**
   *@brief receives (stores) multiples values as inputs
   *@param data vector of values to store
   */
  h_pattern & receive_input(std::vector<double>);

  /**
   *@brief receives (stores) multiple values as expected outputs
   *@param data the expected result components to store
   */
  h_pattern & receive_ouput(std::vector<float>);

  /**
   *@brief receives (stores) inputs values from a stream
   *@param in stream where we get the values
   */
  h_pattern & receive_input(std::istream&);

  /**
   *@brief receives (stores) outputs values from a stream
   *@param in stream where we get the values
   */
  h_pattern & receive_ouput(std::istream&);

  /**
   *@brief accesses the i-th input
   *@param pos position of the input in the set
   *@return the i-th input value of the h_pattern
   */
  double input(int);

  /**
   *@brief accesses the i-th output
   *@param pos position of the output in the set
   *@return the i-th output value of the h_pattern
   */
  float output(int);

  /**
   *@brief accesses the set of inputs
   *@return the set inputs value of the h_pattern
   */
  std::vector<double> & inputs();

  /**
   *@brief accesses the set of outputs
   *@return the set outputs value of the h_pattern
   */
  std::vector<float> & outputs();

  /**
   *@brief echo the state fo the h_pattern to standard output stream
   */
  void print();
};

#endif

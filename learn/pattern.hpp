/**
 *@file pattern.hpp
 *@brief a class designed for naural networs learning algorothms
 *@version 0.1
 *@author Josuah Aron
 *@date 03 September August 2012
 *
 */
#ifndef PATTERN_HPP
#define PATTERN_HPP

#include <iostream>
#include <vector>

/**
 *@class pattern
 *@brief designed for learning algorithms
 *make the manipulation of learning examples easier
 *represents a couple (input data, expected ouputs)
 *
 *l_pattern class (light pattern) loads theirs inputs and/or outputs only when needed (from a database)
 */
class pattern
{
protected:
  std::vector<double> _inputs; /*!< inputs to learn*/
  std::vector<float> _outputs; /*!< expected outputs*/

public:
  /**
   *@brief default constructor
   */
  pattern();

  /**
   *@brief copy constructor
   */
  pattern(const pattern&);

  /**
   *@brief destructor
   */
  virtual ~pattern();

  /**
   *@brief operator =
   */
  virtual pattern & operator=(const pattern&)=0;

  /**
   *@brief operator pattern >> ostream
   */
  virtual pattern & operator>>(std::ostream&)=0;

  /**
   *@brief operator ostream << pattern
   */
  friend std::ostream & operator<<(std::ostream&, pattern*);

  /**
   *@brief operator pattern<<double
   *easily receives an input for the example
   */
  virtual pattern & operator<<(double)=0;

  /**
   *@brief operator pattern(double)
   *easily receives an expected output for the example
   */
  virtual pattern & operator()(float)=0;

  /**
   *@brief the number of input data values
   *@return the number of input values
   */
  virtual int inputs_size()=0;

  /**
   *@brief number of output data values
   *@return the number of output values
   */
  virtual int outputs_size()=0;

  /**
   *@brief receives (stores) a value as an input
   *@param value value to store
   */
  virtual pattern & receive_input(double)=0;

  /**
   *@brief receives (stores) a value as an expected output
   *@param value the expected result component to store
   */
  virtual pattern & receive_ouput(float)=0;

  /**
   *@brief receives (stores) multiples values as inputs
   *@param data vector of values to store
   */
  virtual pattern & receive_input(std::vector<double>)=0;

  /**
   *@brief receives (stores) multiple values as expected outputs
   *@param data the expected result components to store
   */
  virtual pattern & receive_ouput(std::vector<float>)=0;

  /**
   *@brief receives (stores) inputs values from a stream
   *@param in stream where we get the values
   */
  virtual pattern & receive_input(std::istream&)=0;

  /**
   *@brief receives (stores) outputs values from a stream
   *@param in stream where we get the values
   */
  virtual pattern & receive_ouput(std::istream&)=0;

  /**
   *@brief accesses the i-th input
   *@param pos position of the input in the set
   *@return the i-th input value of the pattern
   */
  virtual double input(int)=0;

  /**
   *@brief accesses the i-th output
   *@param pos position of the output in the set
   *@return the i-th output value of the pattern
   */
  virtual float output(int)=0;

  /**
   *@brief accesses the set of inputs
   *@return the set inputs value of the pattern
   */
  virtual std::vector<double> & inputs()=0;

  /**
   *@brief accesses the set of outputs
   *@return the set outputs value of the pattern
   */
  virtual std::vector<float> & outputs()=0;

  /**
   *@brief echo the state fo the pattern to standard output stream
   */
  virtual void print()=0;
};

#endif

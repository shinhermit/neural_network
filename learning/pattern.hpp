/**
 *@file pattern.hpp
 *@brief a class designed for naural networs learning algorothms
 *@version 0.1
 *@author Josuah Aron
 *@date 23 August 2012
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
 */
class pattern
{
private:
  std::vector<double> _data; /*!< input data vector*/
  std::vector<float> _expected; /*!< expected ouputs vector*/

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
  ~pattern();

  /**
   *@brief operator =
   */
  pattern & operator=(const pattern&);


  /**
   *@brief operator <<
   *receives a data (input)
   */
  pattern & operator<<(double);

  /**
   *@brief operator <<
   *receives data (inputs)
   */
  pattern & operator<<(std::vector<double>);

  /**
   *@brief operator ()
   *receives an output value (expected value)
   */
  pattern & operator()(float);

  /**
   *@brief operator ()
   *receives 2 output values (expected value)
   */
  pattern & operator()(float, float);

  /**
   *@brief operator ()
   *receives outputs values (expected values)
   */
  pattern & operator()(std::vector<float>);

  /**
   *@brief operator >>
   */
  pattern & operator>>(std::ostream&);

  /**
   *@brief operator >>
   *just to keep std::cout << x style
   */
  friend std::ostream & operator<<(std::ostream&, pattern&);


  /**
   *@brief accesses inner data vector
   *@return input data vector
   */
  std::vector<double> & d();

  /**
   *@brief accesses inner expected outputs vector
   *@return expected ouputs vector
   */
  std::vector<float> & e();
};

#endif

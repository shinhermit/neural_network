/**
 *@file neurals.hpp
 *@brief namespace for neural network's constants
 *@version 0.1
 *@author Josuah Aron
 *@date 20 August 2012
 *
 */

#ifndef NEURALS_HPP
#define NEURALS_HPP

/**
 *@namespace neurals
 *@brief constants declaration
 *The namespace neurals holds useful constants to use as parameters for neuron objects of neural networks
 *
 */
namespace neurals
{
  const float THRESHOLD = 0.5; /*!< activation limit (seuil)*/
  const float UNEVALUATED = -1.0; /*!< output value before any evaluation*/
  const double RND_MIN = -0.5; /*!< min value for random weights init*/
  const double RND_MAX = 0.5; /*!< max value for random weights init*/
  const int MIN_INPUTS = 1; /*!< min number of inputs of a neuron*/

  typedef enum {FEED_FORWARD, BACKWARD_ALLOWED} type;
};

#endif

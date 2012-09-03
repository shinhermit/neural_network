#ifndef LEARNING_HPP
#define LEARNING_HPP

#include <iostream>
#include <cmath>
#include "example.hpp"
#include "network.hpp"

namespace learning 
{
  /**
   *@brief evaluates the quadratic error of a neuron
   *E = sum_(1<=k<=N) (y_k - x_k)², N=nombre d'exemples
   *@param cell the processing neuron
   *@param model a couple of vectors (inputs, expected outputs)
   *@param expected_pos pos of the expected ouput we are considering. Default 0. Do not fix yourself, let the default value
   *@return the mean squared error of the neuron for the expected_pos example
   */
  float quadratic_error(neuron&, std::vector<example>&, int=0);

  /**
   *@brief evaluates the average quadratic error of a perceptron
   *@param perceptor the processing perceptron
   *@param model a couple of vectors (inputs, expected outputs)
   *@return the mean squared error of the neuron for the expected_pos example
   */
  float quadratic_error(perceptron&, std::vector<example>&);

  /**
   *@brief evaluates the average quadratic error of a network, ie of the output layer
   *@param net the processing network
   *@param model a couple of vectors (inputs, expected outputs)
   *@return the mean squared error of the neuron for the expected_pos example
   */
  float quadratic_error(network&, std::vector<example>&);

  /**
   *@brief single neuron learning algorithm
   *learning by the gradient descent algorithm
   *@param alpha learning factor
   *@param cell the student neuron
   *@param examples vector of example, which is a couple (vector of inputs, vector of expected outpus)
   *@param expected_pos pos of the expected ouput we are considering. Default 0. Do not fix yourself, let the default value
   */
  void gradient_descent(double, neuron&, std::vector<example>&, int);

  /**
   *@brief perceptron learning algorithm
   *learning by the gradient descent algorithm
   *@param alpha learning factor
   *@param perceptor the student perceptron
   *@param examples vector of example, which is a couple (vector of inputs, vector of expected outpus)
   */
  void gradient_descent(double, perceptron&, std::vector<example>&);

  /**
   *@brief single neuron learning algorithm
   *learning by the delta rule algorithm, aka Widrow-Hoff algorithm
   *@param alpha learning factor
   *@param cell the student neuron
   *@param examples vector of example, which is a couple (vector of inputs, vector of expected outpus)
   *@param expected_pos pos of the expected ouput we are considering. Default 0. Do not fix yourself, let the default value
   */
  void delta_rule(double, neuron&, std::vector<example>&, int);

  /**
   *@brief perceptron learning algorithm
   *learning by the delta rule algorithm, aka Widrow-Hoff algorithm
   *@param alpha learning factor
   *@param perceptor the student perceptron
   *@param examples vector of example, which is a couple (vector of inputs, vector of expected outpus)
   */
  void delta_rule(double, perceptron&, std::vector<example>&);

  /**
   *@brief finds the weight index of a connection (backward search)
   *Actually finds the position of a given predecessor in the predecessor list
   *useful for the backpropagation algorithm.
   *@param pred vector of predecessors
   *@param cell unit to find in the predecessors vector
   *@return position of the unit if found, -1 if not
   */
  int find_in_pred(std::vector<unit>&, unit);

  /**
   *@brief finds the weight index of a connection (backward search)
   *Actually finds the position of a given predecessor in the predecessor list
   *useful for the backpropagation algorithm.
   *@param pred vector of predecessors
   *@param layer position of the layer wher the neuron is
   *@param position of the neuron in the layer
   *@return position of the unit if found, -1 if not
   */
  int find_in_pred(std::vector<unit>&, int, int);

  /**
   *@brief network learning algorithm
   *learning by the back-propagation algorithm
   *@param alpha learning factor
   *@param net the student network
   *@param examples vector of example, which is a couple (vector of inputs, vector of expected outpus)
   */
  void backpropagation(double, network&, std::vector<example>&);

  /**
   *@brief applies backpropagation algorithm until the quadratic error falls below a given limit for each example
   *The condition is on each example because the backpropagation algorithm corrects the weights on each example (genaralization of delta-rule).
   *the returned value allows to know in how many steps the condition was reached.
   *@param alpha learning factor
   *@param net the student network
   *@param examples vector of example, which is a couple (vector of inputs, vector of expected outpus)
   *@param error_limit when the quadratic error falls under this value, the algorithm stops
   *@param max_steps max number of times we apply the backpropagation algorithm. Stops the algorithm evenif error_limit has not been reached. Default 20.
   *@return the number of steps (number of times the backpropagation algorithm was runned).
   */
   int backpropagation_until(double, network&, std::vector<example>&, float, int=20);
};

#endif

#ifndef LEARNING_HPP
#define LEARNING_HPP

#include <iostream>
#include "neuron.hpp"
#include "mlp.hpp"
#include "hopfield.hpp"

namespace learning 
{
  /**
   *@fn
   *single neuron weight correction by the gradient descent learning algorithm for one example
   *@param neuron& unit to train
   *@param std::vector<double>& input data
   *@param float expected output
   *@param int=1 number of iterations
   */
  void gradient_descent(neuron&, std::vector<double>&, float, int=1);

  /**
   *@fn
   *single neuron weight correction by the delta rule learning algorithm (Widrow-Hoff) for one example
   *@param neuron& unit to train
   *@param std::vector<double>& input data
   *@param float expected output
   *@param int=1 number of iterations
   */
  void delta_rule(neuron&, std::vector<double>&, float, int=1);

  /**
   *@fn
   *MLP weights correction by the back propagation algorithm, for one example
   *@param mlp& multi-layered perceptron to train
   *@param std::vector<double>& input data
   *@param std::vector<float>& expected outputs
   *@param int=1 number of iterations
   */
  void back_propagation(mlp&, std::vector<double>&, std::vector<float>&, int=1);

  /**
   *@fn
   *hopfield network weights correction by the hebbien algorithm
   *@param hopfield& hopfield neural network to train
   *@param std::vector<double>& input data
   *@param std::vector<float>& expected outputs
   *@param int=1 number of iterations
   */
  void hebb_rule(hopfield&, std::vector<double>&, std::vector<float>&, int=1);
};

#endif

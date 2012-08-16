#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

class neuron
{
private:
  double _buffer; //accumulator that receive the weighted sum of the currently submitted inputs.
  float _output; // we don't want to recalculate the result evry single tume :)
  std::vector<double> _weights; // table of the weights. Indice 0 is the biais
  int _size; //number of inputs
  int _index; //current input (to be added)

  /**
   *@fn
   *activation function. We use sigmoide function: g(x)= 1/(1+exp(-x))
   *@param double weighted sum of the inputs
   *@return result of the sigmoide function calculation.
   */
  float _activation(double);

public:
  neuron(int=1);
  neuron(const neuron &);
  ~neuron();
  neuron & operator=(const neuron &);

  /**
   *@method
   *randomly sets the weights
   */
  void rnd_weights(double=-0.5, double=0.5);

  /**
   *@method
   *receive a new input, multiply it by it weight and add it to buffer
   *@param double the actual input
   */
  void receive(double);

  /**
   *@method
   *overriding method recive
   *@param vector<double>& vector of inputs
   */
  void receive(vector<double>&);

  /**
   *@method
   *gives the output of the unit.
   *@return float result of the treatment byt the unit
   */
  float evaluate();

  void reset();
  void resize(int=1, double=-0.5, double=0.5);
  floar output();
  double getWeight(int);
  void setWeight(int, double);
};

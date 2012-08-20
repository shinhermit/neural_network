/**
 *@file neuron.hpp
 *@brief base element of our neural networks.
 *@author Josuah ARON
 *@version 0.1
 *@date 19 August 2012
 *
 */

#ifndef NEURON_HPP
#define NEURON_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include "neurals.hpp"

/**
 *@class neuron
 *@brief represents a formal neuron
 *the inputs of the neuron are represented by it's table of weights.
 *It has an index that points the next input to be received.
 *The inputs are weighted and add to an accumulator before the evaluation of the weighted sum by the activation function.
 *the activation function is the sigmoid function.
 */
class neuron
{
private:
  double _buffer; /*!< weighted sum accumulator*/

  float _output; /*!< last evaluated output */

  std::vector<double> _weights; /*!< table of the weights. Indice 0 is the biais*/

  int _size; /*!< number of inputs*/

  int _index; /*!< currently indexed input (and weights)*/

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
  neuron(int=1);

  /**
   *@brief copy constructor
   */
  neuron(const neuron &);

  /**
   *@brief destructor
   */
  ~neuron();

  /**
   *@brief operator =
   */
  neuron & operator=(const neuron &);

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
  void receive(std::vector<double>&);

  /**
   *@brief gives the output of the unit.
   *@return result of the treatment by the unit
   */
  float evaluate();

  /**
   *@brief tell is neuron is active or not
   *@return true if output > 0.5, false if not
   */
  bool is_active()const;

  /**
   *@brief resets the accumulator and the output
   */
  void reset();

  /**
   *@brief accesses the input index value
   *@return position of the index
   */
  int input_index()const;

  /**
   *@brief returns the number of inputs of the neuron
   *@return size of the neuron
   */
  int size()const;

  /**
   *@brief modifies the number of inputs of the neuron
   *@param new_size the new size
   *@param min weight value for eventually new inputs
   *@param max weight value for eventually new inputs
   */
  void resize(int=1, double=neurals::RND_MIN, double=neurals::RND_MIN);

  /**
   *@brief returns the last avaluated output
   *@return last processing result
   */
  float output()const;

  /**
   *@brief returns only 0 or 1
   *Useful to create binary neurons (like in Hopfield architecture)
   *@return last processing result
   */
  short binary_output()const;

  /**
   *@brief the i-th weight of the neuron
   *@param pos index of the weight
   *@return value of the weight
   */
  double getWeight(int);

  /**
   *@brief sets a value for a weight
   *This method is useful to train the neuron (fine tunning the weights)
   *@param pos index of the weight
   *@param value new value
   */
  void setWeight(int, double);

  /**
   *@brief prints the current state of the neuron
   *useful for testing
   */
  void print();
};

#endif

/**
 *@section Example
 *@code
 #include <iostream>
 #include "neuron.hpp"

 using namespace std;

 int main(){
   neuron cell(3); // 3 inputs
   vector<double> data;
   int i;
   double val;

   //Get 3 inputs from the user
   for(i=0; i<3; i++){
     cin >> val;
     cell.receive(val);

     data.push_back(val+i); //useful later
   }
   cout<<"evaluation: "<<cell.evaluate()<<endl;

   //Get 3 inputs from a vector
   cell.receive(data);
   cell.evaluate();
   cout<<"evaluation: "<<cell.output()<<endl;
 }
 *@endcode
 *
 *@section Example
 *@code
#include <iostream>
#include "neuron.hpp"

using namespace std;

int main(){
  cout<<endl<<"Creating neuron(3)..."<<endl;
  neuron cell(3);
  cell.print();
  cin;

  cout<<endl<<"receiving input 1.2 ..."<<endl;
  cell.receive(1.2);
  cell.print();

  cout<<endl<<"receiving input 2.3 ..."<<endl;
  cell.receive(2.3);
  cell.print();

  cout<<endl<<"receiving input 3.4 ..."<<endl;
  cell.receive(3.4);
  cell.print();

  cout<<endl<<"running neural evaluation ..."<<endl;
  cell.evaluate();
  cell.print();

  cout<<endl<<"receiving input vector (0.1, 0.2, 0.3) ..."<<endl;
  vector<double> data;
  data.push_back(0.1);
  data.push_back(0.2);
  data.push_back(0.3);
  try{
  cell.receive(data);
  }
  catch(string e){
    cout<<endl<<e<<endl;
    return 1;
  }
  cell.print();

  cout<<endl<<"Running neural evaluation ..."<<endl;
  cell.evaluate();
  cell.print();

  cout<<endl<<"changing weights ..."<<endl;
  cell.setWeight(1, 0.2);
  cell.setWeight(2, 0.2);
  cell.setWeight(3, 0.3);
  cell.print();

  cout<<endl<<"testing observers methods ..."<<endl;
  cout<<"size(): "<<cell.size()<<endl;
  cout<<"input_index(): "<<cell.input_index()<<endl;
  cout<<"output(): "<<cell.output()<<endl;
  cout<<"binary_output(): "<<cell.binary_output()<<endl;
  cout<<"is_active(): "<<cell.is_active()<<endl;
  cout<<"getWeight() 1: "<<cell.getWeight(1)<<" | 2: "<<cell.getWeight(2)<<" | 3: "<<cell.getWeight(3)<<endl;
  return 0;
}
 *@endcode
 */

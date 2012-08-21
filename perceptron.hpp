/**
 *@file perceptron.hpp
 *@brief defining the perceptron.
 *@author Josuah ARON
 *@version 0.1
 *@date 19 August 2012
 *
 */

#ifndef PERCEPTRON_HPP
#define PERCEPTRON_HPP

#include "neuron.hpp"

/**
 *@class perceptron
 *@brief a group of neurons
 *
 *we choose direct access because we don't need fast modifications of the structure, but fast processings
 *we don't say at first which criteria groups some neurons into a perceptron, evenif it's generally admitted that neuron's in a perceptron have no link to each others.
 *Our architecture actually allows any link between neurons, so the criteria can be different.
 *The perceptron can receive the information value after value or as a vector
 *it gives it's output as a vector.
 */
class perceptron
{
private:
  std::vector<neuron> _neurons; /*!< neurons of the perceptron*/

public:
  /**
   *@brief default constructor
   */
  perceptron();

  /**
   *@brief constructor
   *creates an homogenous perceptron ie in wich all neurons have the same number of inputs
   *@param size number of neurons of the perceptron
   *@param neuron_size size of neurons ie number of inputs of the neurons
   */
  perceptron(int, int=1);

  /**
   *@brief copy constructor
   */
  perceptron(const perceptron&);

  /**
   *@brief destructor
   */
  ~perceptron();

  /**
   *@brief operator =
   */
  perceptron & operator=(const perceptron&);

  /**
   *@brief operator []
   *accesses a neuron of the perceptron
   *@param index position of the neuron in the perceptron
   *@return reference of the neuron
   */
  neuron & operator[](int);

  /**
   *@brief operator <<
   */
  friend std::ostream & operator<<(std::ostream&, const perceptron&);

  /**
   *@brief operator <<
   *equivalent to perceptron::receive(double)
   */
  perceptron & operator<<(double);

  /**
   *@brief operator <<
   *equivalent to perceptron::receive(std::vector<double>&)
   */
  perceptron & operator<<(const std::vector<double>&);

  /**
   *@brief operator <<
   *adds a neuron at the end of the perceptron
   */
  perceptron & operator<<(neuron);


  /**
   *@brief size of the perceptron
   *@return number of neurons of the perceptron
   */
  int size()const;

  /**
   *@brief changes the size of the perceptron
   *usefull to remove at once the last neurons of the perceptron
   *@param size new size
   */
  void resize(int=1);

  /**
   *@brief inserts a neuron in the perceptron
   *@param cell new neuron to add
   *@param pos where we want to add the neuron in the perceptron
   */
  void insert(neuron, int);

  /**
   *@brief removes a neuron from the perceptron
   *@param index position of the neuron in the perceptron
   */
  void remove(int);


  /**
   *@brief sets random weights for all the neurons
   *Actually, simply spreads the neuron::rnd_weights() throw all the neurons of the perceptron
   *@param min min weight value
   *@param max max weight value
   */
  void rnd_weights(double=-0.5, double=0.5);

  /**
   *@brief receives a single input
   *the perceptron spreads the value to all it's neurons
   *@param value value of the input
   */
  void receive(double);

  /**
   *@brief receives multiple values
   *@param data values to receive
   */
  void receive(std::vector<double>);

  /**
   *@brief processes the data
   */
  void evaluate();

  /**
   *@brief result of the treatment
   *@return vector of the ouputs of the neurons of the perceptron
   */
  std::vector<float> output();

  /**
   *@brief resets neuron
   *does not reset weights (use rnd_weights() method)
   */
  void reset();


  /**
   *@brief prints the current state of the neuron
   *useful for testing
   */
  void print();
};

#endif







/**
 *@section Examples
 *@subsection Homogenous perceptron
 *@code
#include <iostream>
#include "perceptron.hpp"

using namespace std;

int main(){
  std::vector<double> data1, data2, data3;
  std::vector<float> output;
  int i, size;
  
  //homogenous perceptron
  cout<<endl<<"Creating an homogenous perceptron of 3 neurons each having 5 inputs..."<<endl;
  perceptron perceptor(3, 5);
  perceptor.print();

  cout<<endl<<"Receiving a single value 0.1..."<<endl;
  perceptor.receive(0.1);
  cout << perceptor;

  cout<<endl<<endl<<"Receiving values 0.2, 0.3, 0.4 and 0.5..."<<endl;
  perceptor<<0.2<<0.3<<0.4<<0.5;
  cout << perceptor;

  cout<<endl<<endl<<"Evaluating the perceptron..."<<endl;
  perceptor.evaluate();
  cout << perceptor;

  cout<<endl<<endl<<"Receiving multiple values from vector (1.1, 1.2, 1.3, 1.4, 1.5)..."<<endl;
  for(i=1; i<=5; i++) data1.push_back(1+i*0.1);
  perceptor << data1;
  cout << perceptor;

  cout<<endl<<endl<<"Evaluating the perceptron"<<endl;
  perceptor.evaluate();
  cout << perceptor;

  cout<<endl<<endl<<"Receiving multiple vectors (2.1, 2.2) and (3.3, 3.4, 3.5)..."<<endl;
  for(i=1; i<=2; i++) data2.push_back(2+i*0.1);
  for(i=3; i<=5; i++) data3.push_back(3+i*0.1);
  perceptor << data2 << data3;
  cout << perceptor;

  cout<<endl<<endl<<"Evaluating the perceptron..."<<endl;
  perceptor.evaluate();
  cout<<perceptor;

  cout<<endl<<endl<<"Printing output vector..."<<endl;
  output = perceptor.output();
  size = output.size();
  cout<<"[";
  for(i=0; i<size-1; i++)
    cout<<output[i]<<" ";
  if(i<size)
    cout<<output[i];
  cout<<"]"<<endl;
}
 *@endcode

 *@subsection non homogenous perceptron
 *@code
#include <iostream>
#include "perceptron.hpp"

using namespace std;

int main(){
  std::vector<double> data;
  
  //non homogenous perceptron
  cout<<endl<<"Creating an empty perceptron..."<<endl;
  perceptor = perceptron();
  cout << perceptor;

  cout<<endl<<endl<<"Adding a neuron of 3 inputs..."<<endl;
  perceptor.insert(neuron(3), 0);
  cout << perceptor;

  cout<<endl<<endl<<"Adding 2 neurons, 2 inputs and 4 inputs..."<<endl;
  perceptor << neuron(2) << neuron(4);
  cout << perceptor;

  cout<<endl<<endl<<"Inserting a neuron of 1 input at pos 1..."<<endl;
  perceptor.insert(neuron(1), 1);
  cout << perceptor;

  cout<<endl<<endl<<"Receiving values from vector (1 1 0 1)..."<<endl;
  data = vector<double>(1,1);
  data[2] = 0;
  perceptor << data;
  cout << perceptor;

  cout<<endl<<endl<<"Duplicating the perceptron..."<<endl;
  perceptron copy(perceptor);

  cout<<endl<<endl<<"Resetting one of the two perceptrons..."<<endl;
  copy.reset();
  cout << "p1: " << perceptor;
  cout << endl << "p2: " << copy;

  cout<<endl<<endl<<"Evaluating the other perceptron"<<endl;
  perceptor.evaluate();
  cout << perceptor << endl;
  return 0;
}
 *@endcode
 */

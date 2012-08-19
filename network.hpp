#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <list>
#include "perceptron.hpp"
#include "synaptic.hpp"

class network
{
public:
  typedef std::list<synaptic> synaptics;

private:
  std::vector<perceptron> _layers;
  std::vector<synaptics> _connexions;

public:
  /**
   *@method
   *default constructor
   */
  network();

  /**
   *@method
   *constructor
   *creates a network that contains a number of layer given as first parameter, each containing the same number of neurons (second parameter), and all neurons having the same number of inputs (third parameter)
   *@param int=1 number of layers in the network
   *@param int=1 number of neurons in each layer
   *@param int=1 number of inputs of each neurons
   */
  network(int=1, int=1, int=1);

  /**
   *@method
   *copy constructor
   */
  network(const network&);

  /**
   *@method
   *destructor
   */
  ~network();

  /**
   *@method
   *operator =
   */
  network & operator=(const network&);


  /**
   *@method
   *adds a new neuron into the network
   *@param int layer number
   *@param neuron object to add
   */
  void add_neuron(int, neuron);

  /**
   *@method
   *removes a neuron (and all the connections it is implied in)
   *@param int parent layer index
   *@para int neuron's position in the layer
   */
  void rmv_neuron(int, int);

  /**
   *@method
   *adds a new layer into the network
   *@param perceptron layer to add
   */
  void add_layer(perceptron);

  /**
   *@method
   *removes a layer (and all the connections it's neurons are implied in)
   *@param int index of layer in the network
   */
  void rmv_layer(int);

  /**
   *@method
   *adds a number of homogenous layers
   *@param int number of layers to add
   *@param int layer size (number of neurons)
   *@param int neuron size (number of inputs)
   */
  void add_layers(int, int, int);

  /**
   *@method
   *removes layer from the index given as first argument to the index given as second
   *@param int begin index
   *@param int end index
   */
  void rmv_layers(int,int);

  /**
   *@method
   *tells if a given unti describes an actual neuron of the network
   *@param unit tested unit describer object
   *@return bool boolean response
   */
  bool valid_unit(unit);

  /**
   *@method
   *tells if a given connection (synaptic object) is registered in the network
   *@param synaptic tested synaptic connection
   *@return bool boolean response
   */
  bool registered_connection(synaptic);

  /**
   *@method
   *tells if two unit are connected in the network
   *@param unit source unit
   *@param destination unit
   *@return bool boolean response
   */
  bool are_connected(unit,unit);

  /**
   *@method
   *creates a new connection between two neurons
   *the unit object identifies a neurons, by a pairs (int layer, int position)
   *@param unit source unit
   *@param unit destination unit
   */
  void connect(unit, unit);

  /**
   *@method
   *creates a new connection between two neurons
   *@param int source neuron's layer
   *@param int source neuron's position
   *@param int destination neuron's layer
   *@param int destination neuron's position
   */
  void connect(int, int, int, int);

  /**
   *@method
   *remove a connection from the network
   *@param synaptic the connection we want to delete
   */
  void disconnect(synaptic);

  /**
   *@method
   *remove a connection from the network
   *@param unit source unit
   *@param unit destination unit
   */
  void disconnect(unit,unit);

  /**
   *@method
   *remove all the connection in wich appears a unit (either as source or destination)
   *@param unit the unit we want to completly disconnect
   */
  void disconnect_all(unit);

  /**
   *@method
   *gets the inputs of a layer from it's neurons synaptic connections
   *@param int layer's index in the network
   */
  void synaptic_injection(int);


  /**
   *@method
   *return a vector that contains all the units into which a certains unit inject its output (successors)
   *@param unit& the unit of which we want the successors
   *@return std::vector<unit> successors of the given unit
   */
  std::vector<unit> succ(unit&);

  /**
   *@method
   *return a vector that contains all the units into which a certains unit inject its output (successors)
   *@param int the source unit's layer number
   *@param int the source unit's position
   *@return std::vector<unit> successors of the given unit
   */
  std::vector<unit> succ(int,int);

  /**
   *@method
   *return a vector that contains all the units fromo which a certains unit receives an intput (predecessors)
   *@param unit& the unit of which we want the predecessors
   *@return std::vector<unit> predecessors of the given unit
   */
  std::vector<unit> pred(unit&);

  /**
   *@method
   *return a vector that contains all the units from which a certains unit receives an input (predecessors)
   *@param int the destination unit's layer number
   *@param int the destination unit's position
   *@return std::vector<unit> successors of the given unit
   */
  std::vector<unit> pred(int, int);

  /**
   *@method
   *receives a single input value into the input layer (first layer)
   *@param double value of the input
   */
  void receive(double);

  /**
   *@method
   *receives a set of input values the input layer
   *@param std::vector<double> values to receive
   */
  void receive(std::vector<double>);

  /**
   *@method
   *recons the outputs of all the layers of the network
   */
  void evaluate();

  /**
   *@method
   *return a vector that contains the results of the neurons of the output layer (last layer) of the network
   *@return std::vector<float> vector of the ouputs of the neurons of the perceptron
   */
  std::vector<float> output();

  /**
   *@method
   *resets all the layers of the network
   */
  void reset();
};

#endif

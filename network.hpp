/**
 *@file network.hpp
 *@brief generic neural network
 *@version 0.1
 *@author Josuah Aron
 *@date 10 August 2012
 *
 */

#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <list>
#include "perceptron.hpp"
#include "synaptics.hpp"

/**
 *@class network
 *@brief represents a neural network
 *
 *the network is a set of perceptrons, called layers
 *It receives values from outside the network throw the input layer and gives its results throw the output layer
 *
 *Remember:
 *@li the intput layer is the first layer
 *@li the output layer is the last layer
 *
 *In feed forward networks, connections between layers occur either:
 *@li in the same layer
 *@li from "left" to "right", meaning low layer indices to higher indices
 *
 *The neurons in a perceptron can have any sort of connections
 *The layered architecture makes it easier to look up in the network (for example, methods succ(unit) and pred(unit)
 *
 *The neurons are identified by objects of the class unit
 *Connexions are represented by the class synaptic
 *
 *Each layer has it's set of connections, which contains only incoming connections (what we need to evaluate it's ouput)
 *the layers and sets of connections are in 2 std::vectors
 *so the vectors have both the same number of elements
 *
 *Note for recurrent networks:
 *@li at time t=0, the input layer gets it's inputs from outside the network via network::operator<<(vector) or network::receive(vector).
 *@li at time t>0, the input layer (like other layers) gets it's inputs from inside the network via network::synaptic_injection(i)
*/
class network
{
private:
  std::vector<perceptron> _layers;
  std::vector<synaptics> _connexions;

public:
  /**
   *@brief default constructor
   */
  network();

  /**
   *@brief constructor
   *creates a network that contains a number of layer given as first parameter, each containing the same number of neurons (second parameter), and all neurons having the same number of inputs (third parameter)
   *@param layer_num number of layers in the network
   *@param neurons_per_layer number of neurons in each layer
   *@param inputs_per_neuron number of inputs of each neurons
   */
  network(int, int=1, int=1);

  /**
   *@brief copy constructor
   */
  network(const network&);

  /**
   *@brief destructor
   */
  ~network();

  /**
   *@brief operator =
   */
  network & operator=(const network&);

  /**
   *@brief operator >>
   *sends the current state of the network as a string
   */
  network & operator>>(std::ostream&);

  /**
   *@brief operator <<
   *just to keep std::cout << x style
   */
  friend std::ostream & operator<<(std::ostream&, network&);

  /**
   *@brief operator <<
   *equivalent to network::add_layer(perceptron)
   */
  network & operator<<(perceptron);

  /**
   *@brief operator <<
   *equivalent to network::receive(double)
   */
  network & operator<<(double);

  /**
   *@brief operator <<
   *equivalent to network::receive(std::vector<double>&)
   */
  network & operator<<(std::vector<double>&);


  /**
   *@brief adds a neuron into the network
   *@param layer layer indice in the network
   *@param cell neuron object to add
   */
  void add_neuron(int, neuron);

  /**
   *@brief removes a neuron
   *also removes all the connections where the neuron appears
   *@param layer parent layer index
   *@para pos neuron's position in the layer
   */
  void rmv_neuron(int, int);

  /**
   *@brief adds a layer into the network
   *@param layer layer (perceptron) to add
   *@param pos if != -1, inserts at given position.
   */
  void add_layer(perceptron, int=-1);

  /**
   *@brief removes a layer
   *also remove all the connections where the neurons of the layer appear
   *@param layer index of layer in the network
   */
  void rmv_layer(int);

  /**
   *@brief adds a number of homogenous layers
   *@param how_many number of layers to add
   *@param layer_size number of neurons of each layer
   *@param neuron_size number of inputs of each neuron
   */
  void add_layers(int, int, int);

  /**
   *@brief removes layers from the index given as first argument to the index given as second
   *@param begin remove layers from this indice
   *@param end remove layer until this indice
   */
  void rmv_layers(int,int);

  /**
   *@brief tells if a given unit describes an actual neuron of the network
   *@param cell neuron describer we test
   *@return boolean response
   */
  bool valid_unit(unit);

  /**
   *@brief tells if a given connection (synaptic object) is registered in the network
   *@param synapse neural connection we are testing
   *@return boolean response
   */
  bool registered_connection(synaptic);

  /**
   *@brief tells if a given connection (synaptic object) is registered in the network
   *@param src_unit outgoing unit of the connexion
   *@param dst_unit incoming unit of the connexion
   *@return boolean response
   */
  bool registered_connection(unit, unit);

  /**
   *@brief tells if a given connection (synaptic object) is registered in the network
   *@param int outputing unit's layer
   *@param int outputing unit's position
   *@param int inputing unit's layer
   *@param int inputing unit's position
   *@return boolean response
   */
  bool registered_connection(int,int, int,int);

  /**
   *@brief finds a neural connection in the network
   *the layer where the connection msut be found if given by the synapse ( synaptic::layer() )
   *finds the position a neural connection in the layer's connections set
   *@param synapse the connection we look for
   *@return the position of the connection in the layer's list of connections if found, -1 if not
   */  
  int find_connection(synaptic);

  /**
   *@brief finds a neural connection in the network
   *the layer where the connection msut be found if given by the synapse ( synaptic::layer() )
   *finds the position a neural connection in the layer's connections set
   *@param src outputing unit
   *@param dst intputing unit
   *@return the position of the connection in the layer's list of connections if found, -1 if not
   */  
  int find_connection(unit, unit);

  /**
   *@brief finds a neural connection in the network
   *the layer where the connection msut be found if given by the synapse ( synaptic::layer() )
   *finds the position a neural connection in the layer's connections set
   *@param int outputing unit's layer
   *@param int outputing unit's position
   *@param int inputing unit's layer
   *@param int inputing unit's position
   *@return the position of the connection in the layer's list of connections if found, -1 if not
   */  
  int find_connection(int,int, int,int);

  /**
   *@brief tells if two unit are connected in the network
   *@param src outputing unit
   *@param dst intputing unit
   *@return boolean response
   */
  bool are_connected(unit,unit);

  /**
   *@brief tells if two unit are connected in the network
   *@param int outputing unit's layer
   *@param int outputing unit's position
   *@param int inputing unit's layer
   *@param int inputing unit's position
   *@return boolean response
   */
  bool are_connected(int,int, int,int);

  /**
   *@brief creates a new connection between two units
   *the unit object identifies a neurons, by a pairs (int layer, int position)
   *@param src outputing unit
   *@param dst inputing unit
   */
  void connect(unit, unit);

  /**
   *@brief creates a new connection between two neurons
   *@param int outputing unit's layer
   *@param int outputing unit's position
   *@param int inputing unit's layer
   *@param int inputing unit's position
   */
  void connect(int, int, int, int);

  /**
   *@brief removes a connection from the network
   *@param synapse the connection we want to delete
   */
  void disconnect(synaptic);

  /**
   *@brief remove a connection from the network
   *@param src outputing unit
   *@param dst inputing unit
   */
  void disconnect(unit,unit);

  /**
   *@brief remove a connection from the network
   *@param int outputing unit's layer
   *@param int outputing unit's position
   *@param int inputing unit's layer
   *@param int inputing unit's position
   */
  void disconnect(int,int,int,int);

  /**
   *@brief removes every incoming connections to a unit
   *this method removes all the connection where the given unit receives  an input from another unit's output
   *@param cell the unit we want to remove all incoming connections
   */
  void disconnect_incoming(unit);

  /**
   *@brief removes every incoming connections to a unit
   *this method removes all the connection where the given unit receives  an input from another unit's output
   *@param layer outputing unit's layer
   *@param pos outputing unit's position
   */
  void disconnect_incoming(int, int);

  /**
   *@brief removes every outgoing connections to a unit
   *this method removes all the connection where another receives an input from the output of the given unit
   *the second parameter allows to reduce the research space for feed forward networks
   *@param cell the unit we want to remove all outgoing connections
   *@param net_type feed forward only or backward connections allowed ?
   */
  void disconnect_outgoing(unit, neurals::type=neurals::FEED_FORWARD);

  /**
   *@brief removes every outgoing connections to a unit
   *this method removes all the connection where another receives an input from the output of the given unit
   *the second parameter allows to reduce the research space for feed forward networks
   *@param layer layer of the unit we want to remove all outgoing connections
   *@param pos position in the layer of the unit we want to remove all outgoing connections
   *@param net_type feed forward only or backward connections allowed ?
   */
  void disconnect_outgoing(int,int, neurals::type=neurals::FEED_FORWARD);

  /**
   *@brief remove all the connection in wich appears a unit
   *->either as outputing or inputing
   *the second parameter allows to reduce the research space for feed forward networks
   *@param cell the unit we want to completly disconnect
   *@param net_type feed forward only or backward connections allowed ?
   */
  void disconnect_all(unit, neurals::type=neurals::FEED_FORWARD);

  /**
   *@brief remove all the connection in wich appears a unit
   *->either as outputing or inputing
   *the second parameter allows to reduce the research space for feed forward networks
   *@param layer layer of the unit we want to completly disconnect
   *@param pos position in the layer of the unit we want to completly disconnect
   *@param net_type feed forward only or backward connections allowed ?
   */
  void disconnect_all(int,int, neurals::type=neurals::FEED_FORWARD);

  /**
   *@brief gets the inputs of a layer from it's neurons synaptic connections
   *@param layer_index the layer's position in the network. Default: input layer.
   */
  void synaptic_injection(int=0);


  /**
   *@brief successors of a unit
   *all the units that receive their inputs from the given unit
   *@param src_unit the unit of which we want the successors
   *@param net_type the of the connections of the network: feed forward only, or feed backward allowed ?
   *@return std::vector<unit> of the successors of the given unit
   */
  std::vector<unit> succ(unit, neurals::type=neurals::FEED_FORWARD);

  /**
   *@brief successors of a unit
   *all the units that receive their inputs from the given unit
   *@param src_layer indice of tha layer where the given unit is
   *@param src_pos position of the given unit in it's layer
   *@param net_type the of the connections of the network: feed forward only, or feed backward allowed ?
   *@return std::vector<unit> of the successors of the given unit
   */
  std::vector<unit> succ(int,int, neurals::type=neurals::FEED_FORWARD);

  /**
   *@brief predecessors of a unit
   *all the units from which the given unit receives it's inputs
   *@param dst_unit the unit of which we want the predecessors
   *@param net_type the of the connections of the network: feed forward only, or feed backward allowed ?
   *@return std::vector<unit> of the predecessors of the given unit
   */
  std::vector<unit> pred(unit);

  /**
   *@brief predecessors of a unit
   *all the units from which the given unit receives it's inputs
   *@param dst_layer indice of tha layer where the given unit is
   *@param dst_pos position of the given unit in it's layer
   *@param net_type the of the connections of the network: feed forward only, or feed backward allowed ?
   *@return std::vector<unit> predecessors of the given unit
   */
  std::vector<unit> pred(int, int);

  /**
   *@brief receives a single value in the input layer
   *the input layer is the first layer
   *@param value value of the input
   */
  void receive(double);

  /**
   *@brief receives a set of values in the input layer
   *@param data std::vector<double> of inputs
   */
  void receive(std::vector<double>);

  /**
   *@brief processes a single evaluation of the network
   *for feedback networks, use networl::evaluate(int num_of_steps)
   *@param num_of_steps time information (number of steps)
   */
  void evaluate();

  /**
   *@brief evaluates throw time (steps)
   *-->for recurrent networks
   *@param num_of_steps number of times we process recurrent feeding
   */
  void evaluate(int);

  /**
   *@brief last results of the evaluation of the network
   *the components of the vector are the results of the output layer
   *the output layer is the last layer
   *@return std::vector<float> of results of the output layer
   */
  std::vector<float> output();

  /**
   *@brief resets all the layers (perceptrons) of the network
   */
  void reset();

  /**
   *@brief prints the current state of the neuron
   *useful for testing
   */
  void print();
};

#endif

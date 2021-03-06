/**
 *@file heavy_network.hpp
 *@brief generic neural heavy_network
 *@version 0.2
 *@author Josuah Aron
 *@date 10 August 2012
 *
 */

#ifndef HEAVY_NETWORK_HPP
#define HEAVY_NETWORK_HPP

#include <iostream>
#include "heavy_layer.hpp"
#include "network.hpp"

/**
 *@class heavy_network
 *@brief represents a neural heavy_network
 *
 *the heavy_network is a set of perceptrons, called layers
 *It receives values from outside the heavy_network throw the input layer and gives its results throw the output layer
 *
 *Remember:
 *@li the intput layer is the first layer
 *@li the output layer is the last layer
 *
 *The synaptic connections vector is a sorted vector, and researches in that vector is made by dichotomic algorithm.
 *
 *In feed forward heavy_networks, connections between layers occur either:
 *@li in the same layer
 *@li from "left" to "right", meaning low layer indices to higher indices
 *
 *The neurons in a perceptron can have any sort of connections
 *The layered architecture makes it easier to look up in the heavy_network (for example, methods succ(unit) and pred(unit)
 *
 *The neurons are identified by objects of the class unit
 *Connexions are represented by the class synaptic
 *
 *Each layer has it's set of connections, which contains only incoming connections (what we need to evaluate it's ouput)
 *the layers and sets of connections are in 2 std::vectors
 *so the vectors have both the same number of elements
 *
 *Note for recurrent heavy_networks:
 *@li at time t=0, the input layer gets it's inputs from outside the heavy_network via heavy_network::operator<<(vector) or heavy_network::receive(vector).
 *@li at time t>0, the input layer (like other layers) gets it's inputs from inside the heavy_network via heavy_network::synaptic_injection(i)
*/
class heavy_network : public network
{
private:
  std::vector<layer*> _layers; /*!< neurons layers */
  std::map<int,synaptics> _connexions; /*!< layer |--> set of connections*/

  void _deep_layers_copy(const heavy_network&);

  void _deep_layers_clear();

public:
  /**
   *@brief default constructor
   */
  heavy_network();

  /**
   *@brief constructor
   *creates a heavy_network that contains a number of layer given as first parameter, each containing the same number of neurons (second parameter), and all neurons having the same number of inputs (third parameter)
   *@param layer_num number of layers in the heavy_network
   *@param neurons_per_layer number of neurons in each layer
   *@param inputs_per_neuron number of inputs of each neurons
   */
  heavy_network(int, int=1, int=1);

  /**
   *@brief copy constructor
   */
  heavy_network(const heavy_network&);

  /**
   *@brief destructor
   */
  ~heavy_network();

  /**
   *@brief operator =
   */
  heavy_network & operator=(const heavy_network&);

  /**
   *@brief operator = abstract network
   */
  heavy_network & operator=(network&);

  /**
   *@brief operator [] for layers access
   */
  layer * operator[](int);

  /**
   *@brief operator () for neurons access
   */
  neuron * operator()(int,int);

  /**
   *@brief operator >>
   *sends the current state of the heavy_network as a string
   */
  heavy_network & operator>>(std::ostream&);

  /**
   *@brief operator <<
   *just to keep std::cout << x style
   */
  friend std::ostream & operator<<(std::ostream&, heavy_network&);

  /**
   *@brief operator <<
   *equivalent to heavy_network::add_layer(layer)
   */
  heavy_network & operator<<(layer*);

  /**
   *@brief operator <<
   *equivalent to heavy_network::receive(double)
   */
  heavy_network & operator<<(double);

  /**
   *@brief operator <<
   *equivalent to heavy_network::receive(std::vector<double>&)
   */
  heavy_network & operator<<(std::vector<double>&);


  /**
   *@brief number of layers of the heavy_network
   *@return number of layers
   */
  int size()const;

  /**
   *@brief number of layers of the heavy_network
   *@return number of layers
   */
  std::map<int,synaptics> getConnections();

  /**
   *@brief adds a neuron into the heavy_network
   *@param layer layer indice in the heavy_network
   *@param cell neuron object to add
   */
  void add_neuron(int, neuron*);

  /**
   *@brief removes a neuron
   *also removes all the connections where the neuron appears
   *@param layer parent layer index
   *@para pos neuron's position in the layer
   */
  void rmv_neuron(int, int);

  /**
   *@brief adds a layer into the heavy_network
   *@param layer layer (layer) to add
   *@param pos if != -1, inserts at given position.
   */
  void add_layer(layer*, int=-1);

  /**
   *@brief removes a layer
   *also remove all the connections where the neurons of the layer appear
   *@param layer index of layer in the heavy_network
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
   *@brief tells if a given unit describes an actual neuron of the heavy_network
   *@param cell neuron describer we test
   *@return boolean response
   */
  bool valid_cell(int,int);

  /**
   *@brief finds a neural connection in the heavy_network
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
   *@brief tells if a given connection (synaptic object) is registered in the heavy_network
   *@param int outputing unit's layer
   *@param int outputing unit's position
   *@param int inputing unit's layer
   *@param int inputing unit's position
   *@return boolean response
   */
  bool has_connection(int,int, int,int);

  /**
   *@brief creates a new connection between two neurons
   *@param int outputing unit's layer
   *@param int outputing unit's position
   *@param int inputing unit's layer
   *@param int inputing unit's position
   */
  void connect(int, int, int, int);

  /**
   *@brief remove a connection from the heavy_network
   *@param int outputing unit's layer
   *@param int outputing unit's position
   *@param int inputing unit's layer
   *@param int inputing unit's position
   */
  void disconnect(int,int,int,int);

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
   *the second parameter allows to reduce the research space for feed forward heavy_networks
   *@param layer layer of the unit we want to remove all outgoing connections
   *@param pos position in the layer of the unit we want to remove all outgoing connections
   *@param net_type feed forward only or backward connections allowed ?
   */
  void disconnect_outgoing(int,int);

  /**
   *@brief remove all the connection in wich appears a unit
   *->either as outputing or inputing
   *the second parameter allows to reduce the research space for feed forward heavy_networks
   *@param layer layer of the unit we want to completly disconnect
   *@param pos position in the layer of the unit we want to completly disconnect
   *@param net_type feed forward only or backward connections allowed ?
   */
  void disconnect_all(int,int);

  /**
   *@brief gets the inputs of a layer from it's neurons synaptic connections
   *@param layer_index the layer's position in the heavy_network. Default: input layer.
   */
  void synaptic_injection(int=0);


  /**
   *@brief successors of a unit
   *all the units that receive their inputs from the given unit
   *@param layer indice of tha layer where the given unit is
   *@param pos position of the given unit in it's layer
   *@param net_type the of the connections of the heavy_network: feed forward only, or feed backward allowed ?
   *@return sorted std::vector<unit> of the successors of the given unit
   */
  std::vector<unit> succ(int,int);

  /**
   *@brief predecessors of a unit
   *all the units from which the given unit receives it's inputs
   *@param dst_layer indice of tha layer where the given unit is
   *@param dst_pos position of the given unit in it's layer
   *@param net_type the of the connections of the heavy_network: feed forward only, or feed backward allowed ?
   *@return sorted std::vector<unit> predecessors of the given unit
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
   *@brief processes a single evaluation of the heavy_network
   *for feedback heavy_networks, use networl::evaluate(int num_of_steps)
   *@param num_of_steps time information (number of steps)
   */
  void evaluate();

  /**
   *@brief evaluates throw time (steps)
   *-->for recurrent heavy_networks
   *@param num_of_steps number of times we process recurrent feeding
   */
  void evaluate(int);

  /**
   *@brief last results of the evaluation of the heavy_network
   *the components of the vector are the results of the output layer
   *the output layer is the last layer
   *@return std::vector<float> of results of the output layer
   */
  std::vector<float> output();

  /**
   *@brief resets all the layers (layers) of the heavy_network
   */
  void reset();

  /**
   *@brief removes all connections in the network
   */
  void clear_connections();

  /**
   *@brief clears all the content of the network
   */
  void clear();

  /**
   *@brief writes the state of the neuron to a file (any output stream actually)
   */
  void save(std::ostream&);

  /**
   *@brief loads the state of the neuron from a file (any input stream actually)
   */
  void load(std::istream&);

  /**
   *@brief prints the current state of the neuron
   *useful for testing
   */
  void print();
};

#endif

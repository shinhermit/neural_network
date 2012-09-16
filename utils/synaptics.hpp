#ifndef SYNAPTICS_HPP
#define SYNAPTICS_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include "synaptic.hpp"

/**
 *@class synaptics
 *@brief adds a few functionnalities to std::list<synaptics> specialisation
 *I just needed to make use of std::list<synaptics more easier for screen and stream io
 */
class synaptics
{
private:
  std::vector<synaptic> _synapses;

public:
  /**
   *@brief default constructor
   */
  synaptics();

  /**
   *@brief copy constructor
   */
  synaptics(const synaptics&);

  /**
   *@brief destructor
   */
  ~synaptics();

  /**
   *@brief operator =
   */
  synaptics & operator=(const synaptics&);

  /**
   *@brief operator []
   *accesses current element
   */
  synaptic & operator[](int);

  /**
   *@brief operator >>
   *one of the methods I wanted to add to std::list<synaptic>
   *sends the current state of the list to the output stream
   */
  synaptics & operator>>(std::ostream&);

  /**
   *@brief operator <<
   *just to keep cout << style
   */
  friend std::ostream & operator<<(std::ostream&, synaptics&);
  
  /**
   *@brief operator <<
   */
  synaptics & operator<<(synaptic);

  /**
   *@brief
   *@return number of elements
   */
  int size();

  /**
   *adds an element at the given position
   *@param synapse the connection to add
   *@param pos position
   */
  void add(synaptic, int=-1);

  /**
   *@brief remove an element
   *@param pos position of the element
   */
  void remove(int);

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

#ifndef PATTERN_SET
#define PATTERN_SET

#include "pattern.hpp"

class pattern_set
{
public:
  /**
   *@brief default constructor
   */
  pattern_set();

  /**
   *@brief copy constructor
   */
  pattern_set(const pattern_set&);

  /**
   *@brief virtual destructor
   */
  virtual ~pattern_set();

  /**
   *@brief operator =
   */
  virtual pattern_set & operator=(pattern_set&)=0;

  /**
   *@brief operator []. Accesses patterns
   */
  virtual pattern * operator[](int)=0;

  /**
   *@brief operator pattern_set<<pattern*
   *receives ("stores") a pattern
   */
  virtual pattern_set & operator<<(pattern*)=0;

  /**
   *@brief operator pattern_set>>ostream*
   *send pattern state to output stream
   */
  virtual pattern_set & operator>>(std::ostream&)=0;

  /**
   *@brief polymorphic friend operator ostream<<pattern*
   */
  friend std::ostream & operator<<(std::ostream&, pattern_set&);

  /**
   *@brief number of patterns in the set
   */
  virtual int size()const=0;

  /**
   *@brief accesses the patterns list
   *for polymorphism issues
   */
  virtual std::vector<pattern*> patterns()=0;

  /**
   *@brief print the state of the set to standard output
   */
  virtual void print()=0;
};

#endif

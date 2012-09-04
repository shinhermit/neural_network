#ifndef H_PATTERN_SET
#define H_PATTERN_SET

#include "h_pattern.hpp"
#include "pattern_set.hpp"

class h_pattern_set : public pattern_set
{
private:
  std::vector<pattern*> _patterns; /*!< examples of the training set*/

  void _deep_clear();

  void _deep_copy(const h_pattern_set&);

public:
  /**
   *@brief default constructor
   */
  h_pattern_set();

  /**
   *@brief copy constructor
   */
  h_pattern_set(const h_pattern_set&);

  /**
   *@brief destructor
   */
  ~h_pattern_set();

  /**
   *@brief operator =
   */
  h_pattern_set & operator=(const h_pattern_set&);

  /**
   *@brief operator =
   */
  h_pattern_set & operator=(pattern_set&);

  /**
   *@brief operator []. Accesses patterns
   */
  pattern * operator[](int);

  /**
   *@brief operator h_pattern_set<<pattern*
   *receives ("stores") a pattern
   */
  h_pattern_set & operator<<(pattern*);

  /**
   *@brief operator h_pattern_set>>ostream*
   *send pattern state to output stream
   */
  h_pattern_set & operator>>(std::ostream&);

  /**
   *@brief polymorphic friend operator ostream<<pattern*
   */
  friend std::ostream & operator<<(std::ostream&, h_pattern_set&);

  /**
   *@brief number of patterns in the set
   */
  int size()const;

  /**
   *@brief accesses the patterns list
   *for polymorphism issues
   */
  std::vector<pattern*> patterns();

  /**
   *@brief print the state of the set to standard output
   */
  void print();
};

#endif

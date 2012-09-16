#ifndef EASYCONTAINERS
#define EASYCONTAINERS

#include <string>
#include <sstream>
#include <vector>
#include <map>

namespace easyContainers
{

  /**
   *@brief prints the content of a vector
   *the content must have operator >>(std::ostream&), or be of a basic type
   */
  template <typename Type>
  void print_vector(std::vector<Type>&, char=' ');

  /**
   *@method
   *test if an element is in a std::vector
   *@param vector<Type>& std::vector container
   *@param Type value we are looking for in the vector
   *@return bool value has been found ?? true/false
   */
  template <typename Type>
  bool is_in_vector(std::vector<Type> &, Type);

  /**
   *@method
   *find the position of an elt in a vector
   *@param vector<Type>& std::vector container
   *@param Type value of the générique type we are looking for
   *@return the position of the element if found, -1 elsewise.
   */
  template <typename Type>
  int find_in_vector(std::vector<Type> &, Type);

  /**
   *@class create_map
   *a class for std::map initialisation
   *usage:
   *std::map<T,U> m = create_map<T,U>(T key1, U val1)(T key1, U val2)...(T key_n, U val_n)
   */
  template <typename T, typename U>
  class create_map
  {
  private:
    std::map<T, U> m_map;
  public:
    /**
     *@constructor
     *inserts the given (key,val) into the internal map
     *@param T& key first element of a pair<T,U>
     *@param T& key second element of a pair<T,U>
     */
    create_map(const T&, const U&);

    /**
     *@operator ()
     *insert a pair<T,U>
     *the advantage here is the chaining:
     *(T key1, U val1)(T key1, U val2)...(T key_n, U val_n)
     *@param T& key first element of a pair<T,U>
     *@param T& key second element of a pair<T,U>
     */
    create_map<T, U> & operator()(const T&, const U&);

    /**
     *@operator
     *conversion operator (back to std::map)
     */
    operator std::map<T, U>();
  };

  /**
   *@class create_vector
   *a class for std::vector initialisation
   *usage:
   *std::vector<int> v = create_vector<int>(1,2,3)(1,2)(1)
   *you can insert from 1 to 3 values with on brace ()
   */
  template <typename T>
  class create_vector
  {
  private:
    std::vector<T> m_vector;
  public:
    /**
     *@constructor
     *inserts a single element
     *@param T& element to insert
     */
    create_vector(const T&);

    /**
     *@constructor
     *inserts two elements
     *@param T& element to insert
     *@param T& element to insert
     */
    create_vector(const T&, const T&);

    /**
     *@constructor
     *inserts three elements
     *@param T& element to insert
     *@param T& element to insert
     *@param T& element to insert
     */
    create_vector(const T&, const T&, const T&);

    /**
     *@constructor
     *inserts all the elements of the given vector into the new created vector
     *useful to "complete" a vector in order to initialize another one
     *@param std::vector<T>& vector of elements to insert
     */
    create_vector(const std::vector<T>&);

    /**
     *@operator ()
     *inserts single element
     *@param T& element to insert
     */
    create_vector<T> & operator()(const T&);

    /**
     *@operator ()
     *inserts two elements
     *@param T& element to insert
     *@param T& element to insert
     */
    create_vector<T> & operator()(const T&, const T&);

    /**
     *@operator ()
     *inserts three elements
     *@param T& element to insert
     *@param T& element to insert
     *@param T& element to insert
     */
    create_vector<T> & operator()(const T&, const T&, const T&);

    /**
     *@operator ()
     *inserts all the elements of the given vector into the new created vector
     *useful to "complete" a vector in order to initialize another one
     *@param std::vector<T>& vector of elements to insert
     */
    create_vector<T> & operator()(const std::vector<T>&);

    /**
     *@operator
     *conversion operator (back to std::vector)
     */
    operator std::vector<T>();
  };




  /****************************************************************/



  template <typename Type>
  void print_vector(std::vector<Type> & vect, char seperator){
    int i, size;

    size = vect.size();
    for(i=0; i<size-1; i++){
      std::cout<<vect[i]<< seperator << " ";
    }

    if(i < size){
      std::cout<<vect[i];      
    }
  }

  template<typename Type>
  bool is_in_vector(std::vector<Type> & v, Type elt){
    bool trouve;
    int i, len;

    trouve = false;
    len = v.size();
    i = 0;
    while(i < len && !trouve){
      if(v[i] == elt){
	trouve = true;
      }
      else{
	i++;
      }
    }
    return trouve;
  }

  template<typename Type>
  int find_in_vector(std::vector<Type> & v, Type elt){
    bool trouve;
    int i, len;

    trouve = false;
    len = v.size();
    i = 0;
    while(i < len && !trouve){
      if(v[i] == elt){
	trouve = true;
      }
      else{
	i++;
      }
    }

    i = trouve ? i : -1;
    return i;
  }

  template <typename T, typename U>
  create_map<T,U>::create_map(const T& key, const U& val)
  {
    m_map[key] = val;
  }

  template <typename T, typename U>
  create_map<T, U> & create_map<T,U>::operator()(const T& key, const U& val)
  {
    m_map[key] = val;
    return *this;
  }

  template <typename T, typename U>
  create_map<T,U>::operator std::map<T, U>()
  {
    return m_map;
  }
  
  template <typename T>
  create_vector<T>::create_vector(const T& val)
  {
    m_vector.push_back(val);
  }

  template <typename T>
  create_vector<T>::create_vector(const T& val1, const T& val2)
  {
    m_vector.push_back(val1);
    m_vector.push_back(val2);
  }

  template <typename T>
  create_vector<T>::create_vector(const T& val1, const T& val2, const T& val3)
  {
    m_vector.push_back(val1);
    m_vector.push_back(val2);
    m_vector.push_back(val3);
  }

  template <typename T>
  create_vector<T>::create_vector(const std::vector<T> & v)
  {
    int i, len;
    len = v.size();
    for(i=0; i<len; i++){
      m_vector.push_back(v[i]);
    }
  }

  template <typename T>
  create_vector<T> & create_vector<T>::operator()(const T& val)
  {
    m_vector.push_back(val);
    return *this;
  }

  template <typename T>
  create_vector<T> & create_vector<T>::operator()(const T& val1, const T& val2)
  {
    m_vector.push_back(val1);
    m_vector.push_back(val2);
    return *this;
  }

  template <typename T>
  create_vector<T> & create_vector<T>::operator()(const T& val1, const T& val2, const T& val3)
  {
    m_vector.push_back(val1);
    m_vector.push_back(val2);
    m_vector.push_back(val3);
    return *this;
  }

  template <typename T>
  create_vector<T> & create_vector<T>::operator()(const std::vector<T> & v)
  {
    int i;

    for(i=0; i<v.size(); i++){
      m_vector.push_back(v[i]);
    }
    return *this;
  }

  template <typename T>
  create_vector<T>::operator std::vector<T>()
  {
    return m_vector;
  }
};

#endif

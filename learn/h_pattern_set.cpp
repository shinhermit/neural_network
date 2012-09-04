#include "h_pattern_set.hpp"

void h_pattern_set::_deep_clear(){
 int i, size;

  size = _patterns.size();
  for(i=0; i<size; i++){
    delete _patterns[i];
  }
  _patterns.clear();
}

void h_pattern_set::_deep_copy(const h_pattern_set & source){
  int i, size;

  size = source._patterns.size();
  for(i=0; i<size; i++){
    _patterns.push_back( new h_pattern() );
    *_patterns[i] = *source._patterns[i];
  }
}

h_pattern_set::h_pattern_set(){}

h_pattern_set::h_pattern_set(const h_pattern_set & source){
  _deep_copy(source);
}

h_pattern_set::~h_pattern_set(){
  _deep_clear();
}

h_pattern_set & h_pattern_set::operator=(const h_pattern_set & source){
  _deep_clear();
  _deep_copy(source);

  return *this;
}

h_pattern_set & h_pattern_set::operator=(pattern_set & source){
  int i, size;
  std::vector<pattern*> src_patterns;

  _deep_clear();

  src_patterns = source.patterns();

  size = src_patterns.size();
  for(i=0; i<size; i++){
    _patterns.push_back( new h_pattern() );
    *_patterns[i] = *src_patterns[i];
  }

  return *this;
}

pattern * h_pattern_set::operator[](int pos){
  if( 0<=pos && pos<(int)_patterns.size() ){
    return _patterns[pos];
  }
  else{
    throw std::string("exception. Given indice is out of range.");
  }
  return NULL;
}

h_pattern_set & h_pattern_set::operator<<(pattern * example){

  if(!example)
    example = new h_pattern();

  _patterns.push_back(example);

  return *this;
}

h_pattern_set & h_pattern_set::operator>>(std::ostream & out){
  int i, size;

  out << "{" << std::endl;
  size = _patterns.size();
  for(i=0; i<size; i++){
    out << _patterns[i];
  }
  out << "}" << std::endl;
  return *this;
}

std::ostream & operator<<(std::ostream & out, h_pattern_set & set){
  set >> out;
  return out;
}

int h_pattern_set::size()const{
  return _patterns.size();
}

std::vector<pattern*> h_pattern_set::patterns(){
  return _patterns;
}

void h_pattern_set::print(){
  int i, size;

  std::cout << "{" << std::endl;
  size = _patterns.size();
  for(i=0; i<size; i++){
    _patterns[i]->print();
  }
  std::cout << "}" << std::endl;
}

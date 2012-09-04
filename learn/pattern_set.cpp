#include "pattern_set.hpp"

pattern_set::pattern_set(){}

pattern_set::pattern_set(const pattern_set & source){}

pattern_set::~pattern_set(){}

pattern_set & pattern_set::operator=(pattern_set & source){
  std::cout<<"calling abstract method pattern_set::operator=(pattern_set&)"<<std::endl;
  return *this;
}

pattern * pattern_set::operator[](int pos){
  std::cout<<"calling abstract method pattern_set::operator[](int)"<<std::endl;
  return NULL;
}

pattern_set & pattern_set::operator<<(pattern * example){
  std::cout<<"calling abstract method pattern_set::operator<<(pattern*)"<<std::endl;
  return *this;
}

pattern_set & pattern_set::operator>>(std::ostream & out){
  std::cout<<"calling abstract method pattern_set::operator>>(std::ostream&)"<<std::endl;
  return *this;
}

std::ostream & operator<<(std::ostream & out, pattern_set * set){
  *set >> out;
  return out;
}

int pattern_set::size()const{
  std::cout<<"calling abstract method pattern_set::size()"<<std::endl;
  return -1;
}

std::vector<pattern*> pattern_set::patterns(){
  std::cout<<"calling abstract method pattern_set::patterns()"<<std::endl;
  return std::vector<pattern*>();
}

void pattern_set::print(){
  std::cout<<"calling abstract method pattern_set::print()"<<std::endl;
}

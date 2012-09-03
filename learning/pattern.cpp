#include "pattern.hpp"

pattern::pattern(){}

pattern::pattern(const pattern & source):_data(source._data), _expected(source._expected){}

pattern::~pattern(){}

pattern & pattern::operator=(const pattern & source){
  _data = source._data;
  _expected = source._expected;
  return *this;
}


pattern & pattern::operator<<(double input){
  _data.push_back(input);
  return *this;
}

pattern & pattern::operator<<(std::vector<double> data){
  _data = data;
  return *this;
}

pattern & pattern::operator()(float output){
  _expected.push_back(output);
  return *this;
}

pattern & pattern::operator()(float output1, float output2){
  _expected.push_back(output1);
  _expected.push_back(output2);
  return *this;
}

pattern & pattern::operator()(std::vector<float> expected){
  _expected = expected;
  return *this;
}

pattern & pattern::operator>>(std::ostream & out){
  int i, size;

  size = _data.size();
  out << "[";
  for(i=0; i<size-1; i++) out << _data[i] << ", ";
  if(i == size-1) out << _data[i];
  out << "]"<<std::endl;

  size = _expected.size();
  out << "[";
  for(i=0; i<size-1; i++) out << _expected[i] << ", ";
  if(i == size-1) out << _expected[i];
  out << "]";
  return *this;
}

std::ostream & operator<<(std::ostream & out, pattern & pattern){
  pattern >> out;
  return out;
}


std::vector<double> & pattern::d(){
  return _data;
}

std::vector<float> & pattern::e(){
  return _expected;
}

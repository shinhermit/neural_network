#include "synaptic.hpp"

synaptic::synaptic():_src( unit(0,0) ), _dst( unit(0,0) ){}

synaptic::synaptic(unit source, unit destination):_src(source), _dst(destination){}

synaptic::synaptic(const synaptic & source):_src(source._src), _dst(source._dst){
}

synaptic::~synaptic(){}

synaptic & synaptic::operator=(const synaptic & source){
  _src = source._src;
  _dst = source._dst;
  return *this;
}

std::ostream & operator<<(std::ostream & out, const synaptic & synapse){
  out<<"{"<<synapse._src<<"-->"<<synapse._dst<<"}";
  return out;
}

bool operator==(const synaptic & synapse1, const synaptic & synapse2){
  return (synapse1._src == synapse2._src && synapse1._dst == synapse2._dst);
}

int synaptic::layer()const{return _dst.layer();}

unit & synaptic::source(){return _src;}

unit & synaptic::dest(){return _dst;}

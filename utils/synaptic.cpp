#include "synaptic.hpp"

synaptic::synaptic():_src( unit(0,0) ), _dst( unit(0,0) ){}

synaptic::synaptic(unit source, unit destination):_src(source), _dst(destination){}

synaptic::synaptic(int src_layer, int src_pos, int dst_layer, int dst_pos):_src( unit(src_layer,src_pos) ), _dst( unit(dst_layer,dst_pos) ){}

synaptic::synaptic(const synaptic & source):_src(source._src), _dst(source._dst){}

synaptic::~synaptic(){}

synaptic & synaptic::operator=(const synaptic & source){
  _src = source._src;
  _dst = source._dst;
  return *this;
}

synaptic & synaptic::operator>>(std::ostream & out){
  out<<"{"<<_src<<"-->"<<_dst<<"}";
  return *this;
}

std::ostream & operator<<(std::ostream & out, synaptic & synapse){
  synapse >> out;
  return out;
}

bool operator==(const synaptic & synapse1, const synaptic & synapse2){
  return (synapse1._src == synapse2._src && synapse1._dst == synapse2._dst);
}

bool operator!=(const synaptic & synapse1, const synaptic & synapse2){
  return !(synapse1 == synapse2);
}

bool operator<(const synaptic & synapse1, const synaptic & synapse2){
  bool less;

  less = false;
  if(synapse1._dst < synapse2._dst)
    less = true;
  else if(synapse1._dst == synapse2._dst && synapse1._src < synapse2._src)
    less = true;

  return less;
}

bool operator>(const synaptic & synapse1, const synaptic & synapse2){
  return !(synapse1 < synapse2 || synapse1 == synapse2);
}

bool operator<=(const synaptic & synapse1, const synaptic & synapse2){
  return (synapse1 < synapse2 || synapse1 == synapse2);
}

bool operator>=(const synaptic & synapse1, const synaptic & synapse2){
  return !(synapse1 < synapse2);
}

int synaptic::layer()const{return _dst.layer();}

unit & synaptic::source(){return _src;}

unit & synaptic::dest(){return _dst;}

void synaptic::save(std::ostream & ofile){  
  _src.save(ofile);
  ofile << std::endl;
  _dst.save(ofile);
}

void synaptic::load(std::istream & ifile){
  _src.load(ifile);
  _dst.load(ifile);
}

void synaptic::print(){
  std::cout<<"{";
  _src.print();
  std::cout<<"-->";
  _dst.print();
  std::cout<<"}";
}

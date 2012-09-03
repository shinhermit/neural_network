#include "unit.hpp"

unit::unit(int layer, int pos):_layer( abs(layer) ), _pos( abs(pos) ){}

unit::unit(const unit & source):_layer(source._layer), _pos(source._pos){}

unit::~unit(){}

unit & unit::operator=(const unit & source){
  _layer = source._layer;
  _pos = source._pos;
  return *this;
}

unit & unit::operator>>(std::ostream & out){
  
  out<<"("<<_layer<<", "<<_pos<<")";
  
  return *this;
}

std::ostream & operator<<(std::ostream& out, unit & cell){

  cell >> out;

  return out;
}

bool operator==(const unit & cell1, const unit & cell2){
  return (cell1._layer == cell2._layer && cell1._pos == cell2._pos);
}

bool operator!=(const unit & cell1, const unit & cell2){
  return !(cell1 == cell2);
}

bool operator<(const unit & cell1, const unit & cell2){
  bool less;

  less = false;
  if(cell1._layer < cell2._layer)
    less = true;
  else if(cell1._layer == cell2._layer && cell1._pos < cell2._pos)
    less = true;

  return less;
}

bool operator>(const unit & cell1, const unit & cell2){
  return !(cell1 < cell2 || cell1 == cell2);
}

bool operator<=(const unit & cell1, const unit & cell2){
  return (cell1 < cell2 || cell1 == cell2);
}

bool operator>=(const unit & cell1, const unit & cell2){
  return !(cell1 < cell2);
}

int unit::layer()const{return _layer;}

int unit::pos()const{return _pos;}

void unit::print(){
  std::cout<<"(layer: "<<_layer<<", position: "<<_pos<<")";
}

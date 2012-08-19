#include "unit.hpp"

unit::unit(int layer, int pos):_layer( abs(layer) ), _pos( abs(pos) ){}

unit::unit(const unit & source):_layer(source._layer), _pos(source._pos){}

unit::~unit(){}

unit & unit::operator=(const unit & source){
  _layer = source._layer;
  _pos = source._pos;
  return *this;
}

bool operator==(const unit & cell1, const unit & cell2){
  return (cell1._layer == cell2._layer && cell1._pos == cell2._pos);
}

int unit::layer()const{return _layer;}

int unit::pos()const{return _pos;}



#include "synaptics.hpp"

synaptics::synaptics(){
  _it = _inner_list.begin();
}

synaptics::synaptics(const synaptics & source):_inner_list(source._inner_list){
  _it = _inner_list.begin();
}

synaptics::~synaptics(){}

synaptics & synaptics::operator=(const synaptics & source){
  _inner_list = source._inner_list;
  _it = _inner_list.begin();
  return *this;
}

void synaptics::operator++(int){
  _it++;
}

void synaptics::operator--(int){
  _it--;
}

synaptic & synaptics::operator()(){
  if(_inner_list.size() > 0){
    if( _it == _inner_list.end() ) _it--;
    return *_it;
  }
  else throw std::string("synaptics::operator()(): attemp to access empty object.");
}

synaptics & synaptics::operator>>(std::ostream & out){
  out<<"[";
  for(_it=_inner_list.begin(); _it!=_inner_list.end(); _it++){
    out << *_it;
  }
  out<<"]";

  return *this;  
}

synaptics & synaptics::operator<<(synaptic synapse){
  _inner_list.push_back(synapse);
  return *this;
}

int synaptics::size(){return _inner_list.size();}

void synaptics::move_cursor(int offset){
  int i;

  if(offset > 0){
    for(i=0; i<offset && _it!=_inner_list.end(); i++)_it++;
  }
  else{
    offset = abs(offset);
    for(i=0; i<offset && _it!=_inner_list.begin(); i++)_it--;
  }
}

void synaptics::set_cursor(int pos){
  int i;
  _it = _inner_list.begin();
  pos = abs(pos);
  for(i=0; i<pos && _it!=_inner_list.end(); i++) _it++;
}

void synaptics::add(synaptic synapse, int pos){
  int size;

  size = _inner_list.size();
  if(pos == -1 || pos == size){
    _inner_list.push_back(synapse);
  }
  else{
    pos = abs(pos);
    if(0 <= pos && pos < size){
      set_cursor(pos);
      _inner_list.insert(_it, synapse);
      set_cursor(0); //I don't want to deal with all the cases :p
    }
    else throw std::string("synaptics::add(synaptic,int) : given position is out of range.");
  }
}

void synaptics::remove(int pos){
  int size;

  size = _inner_list.size();
  pos = abs(pos);
  if(0 <= pos && pos < size){
    set_cursor(pos);
    _inner_list.erase(_it);
    set_cursor(0);
  }
}

void synaptics::print(){
  std::cout<<"("<<std::endl;
  for(_it=_inner_list.begin(); _it!=_inner_list.end(); _it++){
    _it->print();
  }
  std::cout<<")"<<std::endl;
}

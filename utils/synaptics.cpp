#include "synaptics.hpp"

synaptics::synaptics(){}

synaptics::synaptics(const synaptics & source):_synapses(source._synapses){}

synaptics::~synaptics(){}

synaptics & synaptics::operator=(const synaptics & source){
  _synapses = source._synapses;
  return *this;
}

synaptic & synaptics::operator[](int pos){
 
  if( 0 <= pos && pos < (int)_synapses.size() ){
    return _synapses[pos];
  }
  else{
    throw std::string("synaptics::operator[](): given index is out of range.");
  }
}

synaptics & synaptics::operator>>(std::ostream & out){
  int i, size;

  size = _synapses.size();
  out<<"[";
  for(i=0; i < size; i++){
    _synapses[i] >> out;
  }
  out<<"]";

  return *this;  
}

std::ostream & operator<<(std::ostream & out, synaptics & synapses){
  synapses >> out;
  return out;
}

synaptics & synaptics::operator<<(synaptic synapse){
  _synapses.push_back(synapse);
  return *this;
}

int synaptics::size(){return _synapses.size();}

void synaptics::add(synaptic synapse, int pos){
  int size;

  size = _synapses.size();
  if(pos == -1 || pos == size){
    _synapses.push_back(synapse);
  }
  else if(0 <= pos && pos < size){
    pos = abs(pos);
    _synapses.insert(_synapses.begin()+pos, synapse);
  }
  else{
    throw std::string("synaptics::add(synaptic,int) : given position is out of range.");
  }
}

void synaptics::remove(int pos){

  pos = abs(pos);
  if(0 <= pos && pos < (int)_synapses.size()){
    _synapses.erase(_synapses.begin()+pos);
  }
}

void synaptics::save(std::ostream & ofile){  
  int i, size;

  ofile << "{" << std::endl;

  size = _synapses.size();
  for(i=0; i < size; i++){
    _synapses[i].save(ofile);
    ofile << std::endl;
  }

  ofile << "}" << std::endl;
}

void synaptics::load(std::istream & ifile){
  int i;
  std::string line, begin_synaptics, end_synaptics;
  std::istringstream iss;
  synaptic synapse;

  begin_synaptics = "{";
  end_synaptics = "}";

  while( ifile.good() && line == "" ){
    std::getline(ifile, line);
  }

  if(line == begin_synaptics){

    _synapses.clear();

    while( ifile.good() && line != end_synaptics ){

      std::getline(ifile, line);
      iss.clear();
      iss.str(line);
      synapse.load(iss);
      _synapses.push_back(synapse);
    }

  }
  else{
    ifile.unget();
  }

}

void synaptics::print(){
  int i, size;

  size = _synapses.size();
  std::cout<<"("<<std::endl;
  for(i=0; i < size; i++){
    _synapses[i].print();
  }
  std::cout<<")"<<std::endl;
}

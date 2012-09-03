#include "example.hpp"

using namespace std;

int main(){
  example pattern;

  cout<<endl<<endl<<"Creating empty example..."<<endl;
  cout << pattern;

  cout<<endl<<endl<<"Adding input values 0.1, 0.2, 0.3..."<<endl;
  pattern << 0.1 << 0.2 << 0.3;
  cout << pattern;

  cout<<endl<<endl<<"Adding expected ouputs 1.1, 1.2, 1.3..."<<endl;
  pattern(1.1)(1.2)(1.3);
  cout << pattern;

  cout<<endl<<endl<<"Accessing inner vector..."<<endl;
  cout << "first data: "<<pattern.d()[0]<<endl;
  cout << "second expected ouput: "<<pattern.e()[1]<<endl<<endl;

  return 0;
}

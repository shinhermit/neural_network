#include "h_pattern.hpp"

using namespace std;

int main(){
  pattern *  example;

  cout<<endl<<endl<<"Creating empty example..."<<endl;
  example = new h_pattern();
  cout << example;

  cout<<endl<<endl<<"Adding input values 0.1, 0.2, 0.3..."<<endl;
  *example << 0.1 << 0.2 << 0.3;
  cout << example;

  cout<<endl<<endl<<"Adding expected ouputs 1.1, 1.2, 1.3..."<<endl;
  (*example)(1.1)(1.2)(1.3);
  cout << example;

  cout<<endl<<endl<<"Accessing data..."<<endl;
  cout << "first data: "<<example->input(0)<<endl;
  cout << "second expected ouput: "<<example->output(1)<<endl<<endl;

  delete example;

  return 0;
}

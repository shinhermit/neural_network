#include "activation.hpp"

namespace activation
{

  float sigmoid(double x){
    return 1/( 1 + exp(-x) );
  }

  float sigmoid_derivative(double x){
    return sigmoid(x) * ( 1 - sigmoid(x) );
  }
};


#include "learning.hpp"

namespace learning
{
  float quadratic_error(neuron & cell, std::vector<example> & examples, int expected_pos){
    int N, k, acc, expected, error;

    N = examples.size(); //number of examples
    acc = 0;
    for(k=0; k<N; k++){
      
      //each example must have a component that corresponds to the expected output
      if( expected_pos < 0 || expected_pos >= (int)examples[k].e().size() ){
	  throw std::string("learning::quadratic_error(): position of expected ouput is out of range");
	}

      expected = examples[k].e().size() > 0 ? examples[k].e()[expected_pos] : 0;

      cell << examples[k].d();
      cell.evaluate();

      error = expected - cell.output();
      acc += error*error;
    }
    return acc / N;
  }

  float quadratic_error(perceptron & perceptor, std::vector<example> & examples){
    int i, num_of_neurons;
    float sum, error;

    num_of_neurons = perceptor.size();
    error = 0;
    if(num_of_neurons > 0){
      sum = 0;
      for(i=0; i<num_of_neurons; i++){
	try{
	  sum += quadratic_error(perceptor[i], examples, i);
	}
	catch(std::string){
	  throw std::string("learning::quadratic_error(perceptron&,std::vector<example>&): the perceptron has more neurons than the one of the examples has expected outputs.");
	}
      }
      error = sum / (float)num_of_neurons;
    }

    return error;
  }

  float quadratic_error(network & net, std::vector<example> & examples){
    int last, num_of_layers;
    float error;

    error = 0;
    num_of_layers = net.size();
    if(num_of_layers > 0){
      last = num_of_layers - 1;
      try{
      error = quadratic_error(net[last], examples);
      }
      catch(std::string){
	throw std::string("learning::quadratic_error(network&,std::vector<example>&): the network has a layer that has more neurons than the one of the examples has expected outputs.");
      }
    }
    return error;
  }

  void gradient_descent(double alpha, neuron & cell, std::vector<example> & examples, int expected_pos){
    std::vector<double> delta;
    int i, k, num_of_inputs, num_of_examples, num_of_expected;
    float expected;
    double x_i;

    num_of_inputs = cell.size();
    num_of_examples = examples.size();
    delta = std::vector<double>(num_of_inputs);
    for(k=0; k<num_of_examples; k++){

      if( expected_pos < 0 || expected_pos >= (int)examples[k].e().size() ){
	  throw std::string("learning::gradient_descent(): position of expected ouput is out of range");
	  return;
	}

	num_of_expected = examples[k].e().size();
	if(num_of_expected < 1){
	  throw std::string("learning::gradient_descent(double,neuron,std::vector<example>): encountered example with no expected output.");
	  return;
	}

      for(i=0; i<num_of_inputs; i++){

	expected = examples[k].e()[expected_pos];

	cell << examples[k].d();
	cell.evaluate();

	x_i = examples[k].d()[i];

	delta[i] += alpha * ( expected - cell.output() ) * x_i;
      }
    }

    for(i=0; i<num_of_inputs; i++){
      cell.setWeight( i, cell.getWeight(i) + delta[i] );
    }
  }

  void gradient_descent(double alpha, perceptron & perceptor, std::vector<example> & examples){
    int i, num_of_neurons;

    num_of_neurons = perceptor.size();
    for(i=0; i<num_of_neurons; i++){
      try{
      gradient_descent(alpha, perceptor[i], examples, i);
      }
      catch(std::string){
	throw std::string("learning::gradient_descent(double,perceptron&,std::vector<example>&): the perceptron has more neurons than the one of the examples has expected outputs.");
      }
    }
  }

  void delta_rule(double alpha, neuron & cell, std::vector<example> & examples, int expected_pos){
    int i, k, num_of_examples, num_of_inputs, num_of_expected;
    float x_i;
    double expected, delta;

    num_of_examples = examples.size();
    num_of_inputs = cell.size();
    for(k=0; k<num_of_examples; k++){

      num_of_expected = examples[k].e().size();
      if(num_of_expected < 1){
	throw std::string("learning::delta_rule(double,neuron,std::vector<example>): encountered example with no expected output.");
	return;
      }

      for(i=0; i<num_of_inputs; i++){

      if( expected_pos < 0 || expected_pos >= (int)examples[k].e().size() ){
	  throw std::string("learning::delta_rule(): position of expected ouput is out of range");
	  return;
	}

	expected = examples[k].e()[expected_pos];

	cell << examples[k].d();
	cell.evaluate();

	x_i = examples[k].d()[i];

	delta = alpha * ( expected - cell.output() ) * x_i;
	cell.setWeight(i, cell.getWeight(i) + delta);
      }
    }
  }

  void delta_rule(double alpha, perceptron & perceptor, std::vector<example> & examples){
    int i, num_of_neurons;

    num_of_neurons = perceptor.size();
    for(i=0; i<num_of_neurons; i++){
      try{
	delta_rule(alpha, perceptor[i], examples, i);
      }
      catch(std::string){
	throw std::string("learning::delta_rule(double,perceptron&,std::vecto<example>&): the perceptron has more neurons than the one of the examples has expected outputs");
      }
    }
  }

  int find_in_pred(std::vector<unit> & pred, unit cell){
    int i, w_i;
    bool found;
    
    found = false;
    i = 0;
    while( i < (int)pred.size() && !found ){
      if(pred[i] == cell){
	found = true;
      }
      else{
	i++;
      }
    }

    w_i = found ? i : -1;
    return w_i;
  }

  int find_in_pred(std::vector<unit> & pred, int layer, int pos){
    return find_in_pred(pred, unit(layer, pos));
  }

  void back_propagation(double alpha, network & net, std::vector<example> & examples){
    int k, j, i, p, x, y, w_i, last, num_of_examples, num_of_layers, num_of_neurons, num_of_weights;
    std::vector< std::vector<double> > delta;
    float calculated, expected;
    double forward_influence, w;
    std::vector<unit> succ, pred;

    num_of_layers = net.size();
    num_of_examples = examples.size();

    delta = std::vector< std::vector<double> >(num_of_layers);

    for(k=0; k<num_of_examples; k++){
      //evaluating the ouput of the network
      net << examples[k].d();
      net.evaluate();

      //the output layer
      last = net.size()-1;
      num_of_neurons = net[last].size(); //possible issue: what if net has no layer ?
      delta[last] = std::vector<double>(num_of_neurons);
      for(i=0; i<num_of_neurons; i++){
	calculated = net(last,i).output();

	expected = examples[k].e()[i]; //possible issue: what if no expected?

	delta[last][i] = calculated * (1 - calculated) * (expected - calculated);
      }

      //the other layers
      for(j=last-1; j>=0; j++){
	num_of_neurons = net[j].size();
	delta[j] = std::vector<double>(num_of_neurons);
	for(i=0; i<num_of_neurons; i++){
	  calculated = net(j,i).output();

	  //influence: how the cell impacts (the error of) is successors
	  forward_influence = 0;
	  succ = net.succ(j,i); //possible issue: what if no successors ?
	  for(p=0; p<(int)succ.size(); p++){
	    //successor's coordinates to find his delta
	    x = succ[p].layer();
	    y = succ[p].pos();

	    //finding the weight of the connection cell-->current successor
	    pred = net.pred(x,y);
	    w_i = find_in_pred( pred, unit(j,i) );

	    forward_influence += delta[x][y] * net(x,y).getWeight(w_i); //possible issue: what if w_i == -1 ?
	  }

	  delta[j][i] = calculated * (1 - calculated) * forward_influence;
	}
      }
      
      ///////  weights correction /////////
      //input layer
      num_of_neurons = net[0].size();
      for(i=0; i<num_of_neurons; i++){
	num_of_weights = net(0,i).size();
	for(p=0; p<num_of_weights; p++){
	  w = net(0,i).getWeight(p) + alpha * delta[0][i] * examples[k].d()[p]; //possible issue: what not enough inputs in example ?
	  net(0,i).setWeight(p, w);
	}
      }

      //other layers
      for(j=1; j<num_of_layers; j++){
	num_of_neurons = net[j].size();
	for(i=0; i<num_of_neurons; i++){
	  num_of_weights = net(j,i).size();
	  for(p=0; p<num_of_weights; p++){
	    //finding the neuron that injects in weight p
	    pred = net.pred(j,i);
	    x = pred[p].layer(); //possible issue: what if pred has less than p elements ?
	    y = pred[p].pos();
 
	    //correcting weight
	    w = net(j,i).getWeight(p) + alpha * delta[j][i] * net(x,y).output();
	    net(j,i).setWeight(p, w);
	  }
	}
      }

    }//end for examples
  }

  int backpropagation_until(double alpha, network & net, std::vector<example> & examples, float error_limit, int max_steps){
    int steps;
    float error;

    steps = 0;
    error = quadratic_error(net, examples);
    while(error > error_limit && steps < max_steps){
      backpropagation(alpha, net, examples);
      error = quadratic_error(net, examples);
      steps++;
    }

    return steps;
  }
};

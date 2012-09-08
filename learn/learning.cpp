#include "learning.hpp"

namespace learning
{
  float squared_error(neuron & cell, pattern_set & examples, int expected_pos){
    int N, k;
    double expected;
    float error, acc;

    N = examples.size(); //number of examples
    acc = 0;
    for(k=0; k<N; k++){
      
      if( expected_pos < 0 || expected_pos >= examples[k]->outputs_size() ){
	  throw std::string("learning::squared_error(): position of expected ouput is out of range");
	}

      expected = examples[k]->outputs_size() > 0 ? examples[k]->output(expected_pos) : 0;

      cell << examples[k]->inputs();
      cell.evaluate();

      error = expected - cell.output();
      acc += error*error;
    }
    return acc / N;
  }

  float squared_error(layer & perceptron, pattern_set & examples){
    int i, num_of_neurons;
    float sum, error;

    num_of_neurons = perceptron.size();
    error = 0;
    if(num_of_neurons > 0){
      sum = 0;
      for(i=0; i<num_of_neurons; i++){
	try{
	  sum += squared_error(*perceptron[i], examples, i );
	}
	catch(std::string){
	  throw std::string("learning::squared_error(perceptron&,std::vector<example>&): the perceptron has more neurons than the one of the examples has expected outputs.");
	}
      }
      error = sum / (float)num_of_neurons;
    }

    return error;
  }

  float squared_error(network & net, pattern_set & examples){
    int N, k, i, last, num_of_layers, res_size, exp_size;
    double expected, evaluated;
    float error_k, acc_k, squared_error_k, acc;

    N = examples.size();
    acc = 0;
    for(k=0; k<N; k++){
      net << examples[k]->inputs();
      net.evaluate();

      num_of_layers = net.size();
      last = num_of_layers - 1;
      if(num_of_layers > 0){
	res_size = net[last]->size();
	exp_size = examples[k]->outputs_size();

	if(res_size != exp_size){
	  throw std::string("exception! learning::squared_error(network*,pattern_set*): size of network output vector is different from size of expected outputs vector of one example");
	}

	acc_k=0;
	for(i=0; i<res_size; i++){
	  expected = examples[k]->output(i);
	  evaluated = net(last,i)->output();
	  error_k = expected - evaluated;
	  acc_k += error_k * error_k;
	}
	squared_error_k = acc_k / res_size;
      }
      else{
	throw std::string("exception! learning::squared_error(network*,pattern_set*) : the network has no layer");
      }

      acc += squared_error_k;
    }
    return acc / N;
  }

  void gradient_descent(double alpha, neuron & cell, pattern_set & examples, int expected_pos){
    std::vector<double> delta;
    int i, k, num_of_inputs, num_of_examples, num_of_expected;
    float expected;
    double x_i;

    num_of_inputs = cell.size();
    num_of_examples = examples.size();
    delta = std::vector<double>(num_of_inputs);
    for(k=0; k<num_of_examples; k++){

      num_of_expected = examples[k]->outputs_size();
      if( expected_pos < 0 || expected_pos >= num_of_expected ){
	throw std::string("learning::gradient_descent(): position of expected ouput is out of range");
	return;
      }

      if(num_of_expected < 1){
	throw std::string("learning::gradient_descent(double,neuron,std::vector<example>): encountered example with no expected output.");
	return;
      }

      for(i=0; i<num_of_inputs; i++){

	expected = examples[k]->output(expected_pos);

	cell << examples[k]->inputs();
	cell.evaluate();

	x_i = examples[k]->input(i);

	delta[i] += alpha * ( expected - cell.output() ) * x_i;
      }
    }

    for(i=0; i<num_of_inputs; i++){
      cell.setWeight( i, cell.getWeight(i) + delta[i] );
    }
  }

  void gradient_descent(double alpha, layer & perceptron, pattern_set & examples){
    int i, num_of_neurons;

    num_of_neurons = perceptron.size();
    for(i=0; i<num_of_neurons; i++){
      try{
	gradient_descent(alpha, *perceptron[i], examples, i);
      }
      catch(std::string&){
	throw std::string("learning::gradient_descent(double,perceptron&,std::vector<example>&): the perceptron has more neurons than the one of the examples has expected outputs.");
      }
    }
  }

  void delta_rule(double alpha, neuron & cell, pattern_set & examples, int expected_pos){
    int i, k, num_of_examples, num_of_inputs, num_of_expected;
    float x_i;
    double expected, delta;

    num_of_examples = examples.size();
    num_of_inputs = cell.size();
    for(k=0; k<num_of_examples; k++){

      num_of_expected = examples[k]->outputs_size();
      if(num_of_expected < 1){
	throw std::string("learning::delta_rule(double,neuron,std::vector<example>): encountered example with no expected output.");
	return;
      }

      for(i=0; i<num_of_inputs; i++){

	if(expected_pos < 0 || expected_pos >= num_of_expected){
	  throw std::string("learning::delta_rule(): position of expected ouput is out of range");
	  return;
	}

	expected = examples[k]->output(expected_pos);

	cell << examples[k]->inputs();
	cell.evaluate();

	x_i = examples[k]->input(i);

	delta = alpha * ( expected - cell.output() ) * x_i;
	cell.setWeight(i, cell.getWeight(i) + delta);
      }
    }
  }

  void delta_rule(double alpha, layer & perceptron, pattern_set & examples){
    int i, num_of_neurons;

    num_of_neurons = perceptron.size();
    for(i=0; i<num_of_neurons; i++){
      try{
	delta_rule(alpha, *perceptron[i], examples, i);
      }
      catch(std::string){
	throw std::string("learning::delta_rule(double,perceptron&,std::vecto<example>&): the perceptron has more neurons than the one of the examples has expected outputs");
      }
    }
  }

  int find_in_pred(std::vector<unit> & pred, unit cell){
    int first, last, middle, size, pos;
    bool found;

    size = pred.size();
    first = 0;
    last = size-1;
    found = false;
    while(first <= last && !found){

      middle = (first + last) / 2;

      if( pred[middle] == cell ){
	found = true;
      }
      else if( pred[middle] < cell ){
	first = middle + 1;
      }
      else{
	last = middle - 1;
      }

    }

    pos = found ? middle : -1;
    return pos;
  }

  int find_in_pred(std::vector<unit> & pred, int layer, int pos){
    return find_in_pred(pred, unit(layer, pos));
  }

  void backpropagation(double alpha, network & net, pattern_set & examples){
    int k, j, i, p, x, y, pos_w, input, output, num_of_examples, num_of_layers, num_of_neurons, num_of_outputs, num_of_inputs, num_of_expected, num_of_weights;
    std::vector< std::vector<double> > delta;
    float calculated, expected, x_p;
    double forward_influence, w;
    std::vector<unit> succ, pred;

    num_of_layers = net.size();

    if(num_of_layers == 0){
      throw std::string("exception! learning::back_propagation(double,network*,pattern_set*) : the network has no layer.");
    }

    input = 0;
    output = num_of_layers - 1;

    num_of_examples = examples.size();

    delta = std::vector< std::vector<double> >(num_of_layers);

    for(k=0; k<num_of_examples; k++){
      //evaluating the ouput of the network
      net << examples[k]->inputs();
      net.evaluate();

      //the output layer
      num_of_outputs = net[output]->size();
      num_of_expected = examples[k]->outputs_size();

      if(num_of_outputs != num_of_expected){
	throw std::string("exception! learning::back_propagation(double,network*,pattern_set*) : network outputs vector size does not match expected outputs vector size of one example");
      }

      delta[output] = std::vector<double>(num_of_outputs);
      for(i=0; i<num_of_outputs; i++){
	calculated = net(output,i)->output();

	expected = examples[k]->output(i);

	delta[output][i] = -calculated * (1 - calculated) * (expected - calculated);
      }

      //the other layers
      for(j=output-1; j>=0; j--){
	num_of_neurons = net[j]->size();
	delta[j] = std::vector<double>(num_of_neurons);
	for(i=0; i<num_of_neurons; i++){
	  calculated = net(j,i)->output();

	  //influence: how the cell impacts (the error of) is successors
	  forward_influence = 0;
	  succ = net.succ(j,i);
	  for(p=0; p<(int)succ.size(); p++){
	    //successor's coordinates to find his delta
	    x = succ[p].layer();
	    y = succ[p].pos();

	    //finding the weight of the connection cell-->current successor
	    pred = net.pred(x,y);
	    pos_w = find_in_pred( pred, unit(j,i) );

	    if(pos_w == -1){
	      throw std::string("exception! learning::back_propagation(double,network*,pattern_set*) found possible programming paradox: a unit does not appear in the predecessors list of one of his successors.");
	    }

	    forward_influence += delta[x][y] * net(x,y)->getWeight(pos_w);
	  }

	  delta[j][i] = -calculated * (1 - calculated) * forward_influence;
	}
      }
      
      ///////  weights correction /////////
      //input layer
      num_of_neurons = net[0]->size();
      for(i=0; i<num_of_neurons; i++){
	num_of_weights = net(input,i)->size();
	num_of_inputs = examples[k]->inputs_size();

	if(num_of_weights != num_of_inputs){
	  throw std::string("exception! learning::back_propagation(double,network*,pattern_set*): size of an input neuron is greater than size of inputs vector of an example.");
	}

	for(p=0; p<num_of_weights; p++){
	  w = net(input,i)->getWeight(p) - alpha * delta[input][i] * examples[k]->input(p);
	  net(input,i)->setWeight(p, w);
	}
      }

      //other layers
      for(j=1; j<num_of_layers; j++){
	num_of_neurons = net[j]->size();
	for(i=0; i<num_of_neurons; i++){
	  num_of_weights = net(j,i)->size();
	  for(p=0; p<num_of_weights; p++){
	    //finding the neuron that injects in weight p
	    pred = net.pred(j,i);
	    if( pred.size() > 0 ){
	      x = pred[p].layer();
	      y = pred[p].pos();
	      x_p = net(x,y)->output();
	    }
	    else x_p = 0;
 
	    //correcting weight
	    w = net(j,i)->getWeight(p) - alpha * delta[j][i] * x_p;
	    net(j,i)->setWeight(p, w);
	  }
	}
      }

    }//end for examples
  }

  int backpropagation_until(double alpha, network & net, pattern_set & examples, float error_limit, int max_steps){
    int steps;
    float error;

    steps = 0;
    error = squared_error(net, examples);
    while(error > error_limit && steps < max_steps){
      backpropagation(alpha, net, examples);
      error = squared_error(net, examples);
      steps++;
    }

    return steps;
  }
};

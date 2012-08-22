#VARIABLES
src= .
inc= .
obj= .
exe= .
flags= -Wall -g
cc= g++

#CIBLES

all: network

neuron:
	$(cc) -c -I$(inc) $(flags) $(src)/$@.cpp

test_neuron: neuron
	$(cc) -I$(inc) $(flags) $(obj)/*.o $(src)/$@.cpp -o $(exe)/$@.out

unit:
	$(cc) -c -I$(inc) $(flags) $(src)/$@.cpp

test_unit: unit
	$(cc) -I$(inc) $(flags) $(obj)/*.o $(src)/$@.cpp -o $(exe)/$@.out

perceptron: neuron
	$(cc) -c -I$(inc) $(flags) $(src)/$@.cpp

test_perceptron: perceptron
	$(cc) -I$(inc) $(flags) $(obj)/*.o $(src)/$@.cpp -o $(exe)/$@.out

synaptic: unit
	$(cc) -c -I$(inc) $(flags) $(src)/$@.cpp

test_synaptic: synaptic
	$(cc) -I$(inc) $(flags) $(obj)/*.o $(src)/$@.cpp -o $(exe)/$@.out

synaptics: synaptic
	$(cc) -c -I$(inc) $(flags) $(src)/$@.cpp

network: perceptron synaptics
	$(cc) -c -I$(inc) $(flags) $(src)/$@.cpp

test_network: network
	$(cc) -I$(inc) $(flags) $(obj)/*.o $(src)/$@.cpp -o $(exe)/$@.out

cleantemp:
	rm *~

cleanobj:
	rm *.o
distclean:
	rm *.out

cleanall: cleantemp cleanobj distclean
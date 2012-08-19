#VARIABLES
src= .
inc= .
flags= -Wall -g
cc= g++

#CIBLES

all: network

neuron:
	$(cc) -c -I$(inc) $(flags) $(src)/$@.cpp

unit:
	$(cc) -c -I$(inc) $(flags) $(src)/$@.cpp

perceptron: neuron
	$(cc) -c -I$(inc) $(flags) $(src)/$@.cpp

synaptic: unit
	$(cc) -c -I$(inc) $(flags) $(src)/$@.cpp

network: perceptron synaptic
	$(cc) -c -I$(inc) $(flags) $(src)/$@.cpp

cleantemp:
	rm *~

cleanobj:
	rm *.o
distclean:
	rm *.out

cleanall: cleantemp cleanobj distclean
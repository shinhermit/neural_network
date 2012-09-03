#VARIABLES
src= .
inc= -I. -I../inc -I../utils
obj= ../obj
flags= -Wall -g
cc= g++

#CIBLES

all: neuron layer network

neuron:
	$(cc) -c $(inc) $(flags) $(src)/$@.cpp
	mv $@.o $(obj)

layer:
	$(cc) -c $(inc) $(flags) $(src)/$@.cpp
	mv $@.o $(obj)

network:
	$(cc) -c $(inc) $(flags) $(src)/$@.cpp
	mv $@.o $(obj)

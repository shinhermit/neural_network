#VARIABLES
src= .
inc= -I. -I../abstract -I../inc -I../utils
obj= ../obj
flags= -Wall -g
cc= g++

#CIBLES

all: heavy_neuron heavy_layer heavy_network

heavy_neuron:
	$(cc) -c $(inc) $(flags) $(src)/$@.cpp	
	mv $@.o $(obj)

heavy_layer:
	$(cc) -c $(inc) $(flags) $(src)/$@.cpp
	mv $@.o $(obj)

heavy_network:
	$(cc) -c $(inc) $(flags) $(src)/$@.cpp
	mv $@.o $(obj)

#VARIABLES
src= .
inc= -I. -I../abstract -I../inc -I../utils
obj= ../obj
flags= -Wall -g
cc= g++

#CIBLES
cmd = $(cc) -c $(inc) $(flags) $(src)/$@.cpp; mv $@.o $(obj)

all: heavy_neuron heavy_layer heavy_network

heavy_neuron:
	$(cmd)

heavy_layer:
	$(cmd)

heavy_network:
	$(cmd)

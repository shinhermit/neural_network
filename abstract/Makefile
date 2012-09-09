#VARIABLES
src= .
inc= -I. -I../inc -I../utils
obj= ../obj
flags= -Wall -g
cc= g++

#CIBLES

cmd = $(cc) -c $(inc) $(flags) $(src)/$@.cpp; mv $@.o $(obj)

all: neuron layer network

neuron:
	$(cmd)

layer:
	$(cmd)

network:
	$(cmd)

####################################################
## this is just the set-up, no implementation yet ##
####################################################

#VARIABLES
src= .
inc= -I. -I../abstract -I../inc -I../utils
obj= ../obj
flags= -Wall -g
cc= g++

#CIBLES
cmd = $(cc) -c $(inc) $(flags) $(src)/$@.cpp; mv $@.o $(obj)

all: light_neuron light_layer light_network

light_neuron:
	$(cmd)

light_layer:
	$(cmd)

light_network:
	$(cmd)

#VARIABLES
src= .
inc= -I. -I../utils -I../abstract -I../inc -I../heavy_net -I../known -I../models -I../learn
obj= ../obj
exe= ..
flags= -Wall -g
cc= g++

#CIBLES

cmd = $(cc) $(inc) $(flags) $(obj)/*.o $(src)/$@.cpp -o $(exe)/$@.out

test_unit:
	$(cmd)

test_synaptic:
	$(cmd)

test_synaptics:
	$(cmd)

test_neuron:
	$(cmd)

test_layer:
	$(cmd)

test_network:
	$(cmd)

test_models:
	$(cmd)

test_MLP:
	$(cmd)

test_pattern:
	$(cmd)

test_pattern_set:
	$(cmd)

test_xor:
	$(cmd)

test_xor2:
	$(cmd)

test_xor3:
	$(cmd)

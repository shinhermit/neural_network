#VARIABLES
src= .
inc= -I. -I../utils -I../abstract -I../inc -I../heavy_net -I../known -I../models -I../learn
obj= ../obj
exe= ..
flags= -Wall -g
cc= g++
cmd_exe=

#CIBLES

cmd_obj = $(cc) -c $(inc) $(flags) $(src)/$@.cpp; mv $@.o $(obj)

cmd_exe = $(cc) $(inc) $(flags) $(obj)/*.o $(src)/$@.cpp -o $(exe)/$@.out

test_unit:
	$(cmd_obj)

test_synaptic:
	$(cmd_obj)

test_synaptics:
	$(cmd_obj)

test_neuron:
	$(cmd_obj)

test_layer:
	$(cmd_obj)

test_network:
	$(cmd_obj)

test_MLP_model:
	$(cmd_obj)

test_hopfield_model:
	$(cmd_obj)

test_kohonen_model:
	$(cmd_obj)

test_MLP:
	$(cmd_obj)

test_pattern:
	$(cmd_obj)

test_pattern_set:
	$(cmd_obj)

test_backprop:
	$(cmd_obj)

dashboard:
	$(cmd_exe)

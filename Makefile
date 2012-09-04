#VARIABLES
obj= obj
exe= .
flags= -Wall -g
cc= g++

#CIBLES

all: abstracts utils heavies lights trainings all_tests

##### abstracts

neuron:
	cd abstract; make $@

layer:
	cd abstract; make $@

network:
	cd abstract; make $@

abstracts: neuron layer network

clean_abstracts_temp:
	rm abstract/*~

##### Utilities classes

unit:
	cd utils; make $@

synaptic:
	cd utils; make $@

synaptics:
	cd utils; make $@

utils: unit synaptic synaptics

clean_utils_temp:
	rm utils/*~

##### inner data classes (heavy network)

heavy_neuron:
	cd heavy_net; make $@

heavy_layer:
	cd heavy_net; make $@

heavy_network:
	cd heavy_net; make $@

heavies: heavy_neuron heavy_layer heavy_network

clean_heavies_temp:
	rm heavy_net/*~

##### data base classes (light network)

light_neuron:
	cd light_network; make $@

light_layer:
	cd light_network; make $@

light_network:
	cd light_network; make $@

lights: light_neuron light_layer light_network

clean_lights_temp:
	rm light_net/*~

##### learning algorithms

pattern:
	cd learn; make $@

pattern_set:
	cd learn; make $@

h_pattern:
	cd learn; make $@

h_pattern_set:
	cd learn; make $@

learning:
	cd learn; make $@

trainings: pattern pattern_set h_pattern h_pattern_set learn

clean_trainings_temp:
	rm learn/*~

#### tests


test_unit: unit
	cd tests; make $@

test_synaptic: unit synaptic
	cd tests; make $@

test_synaptics: utils
	cd tests; make $@

test_neuron: neuron heavy_neuron
	cd tests; make $@

test_layer: neuron layer heavy_neuron heavy_layer
	cd tests; make $@

test_network: abstracts utils heavies
	cd tests; make $@

test_pattern: pattern h_pattern
	cd tests; make $@

test_pattern_set: pattern pattern_set h_pattern h_pattern_set
	cd tests; make $@

test_learning: abstracts utils heavies trainings
	cd tests; make $@

all_tests: test_neuron test_layer test_unit test_synaptic test_network test_pattern test_learning

clean_tests_temp:
	rm tests/*~

##### cleaning

cleantemp: clean_abstracts_temp clean_utils_temp clean_heavies_temp clean_lights_temp clean_trainings_temp clean_tests_temp

cleanobj:
	rm $(obj)/*.o

distclean:
	rm $(exe)/*.out

cleanall: cleantemp cleanobj distclean
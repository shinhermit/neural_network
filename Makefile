#VARIABLES
obj= obj
exe= .

#CIBLES

all: dashboard

##### abstracts

abs_dir = abstract

abs_cmd = cd $(abs_dir); make $@

neuron:
	$(abs_cmd)

layer:
	$(abs_cmd)

network:
	$(abs_cmd)

abstracts: neuron layer network

clean_abstracts_temp:
	rm -f $(abs_dir)/*~

##### Utilities classes

util_dir = utils

util_cmd = cd $(util_dir); make $@

unit:
	$(util_cmd)

synaptic:
	$(util_cmd)

synaptics:
	$(util_cmd)

models:
	$(util_cmd)

funcs:
	$(util_cmd)

activation:
	$(util_cmd)

utils: unit synaptic synaptics models funcs activation

clean_utils_temp:
	rm -f $(util_dir)/*~

##### inner data classes (heavy network)

hvy_dir = heavy_net

hvy_cmd = cd $(hvy_dir); make $@

heavy_neuron:
	$(hvy_cmd)

heavy_layer:
	$(hvy_cmd)

heavy_network:
	$(hvy_cmd)

heavies: heavy_neuron heavy_layer heavy_network

clean_heavies_temp:
	rm -f $(hvy_dir)/*~

##### data base classes (light network)
## this is just the set-up, no implementation yet

lt_dir = light_net

lt_cmd = cd $(lt_dir); make $@ 

light_neuron:
	$(lt_cmd)

light_layer:
	$(lt_cmd)

light_network:
	$(lt_cmd)

lights: light_neuron light_layer light_network

clean_lights_temp:
	rm -f $(lt_dir)/*~

##### Known architectures
knw_dir = known

knw_cmd = cd $(knw_dir); make $@

heavy_MLP:
	$(knw_cmd)

knwons: heavy_MLP

clean_known_temp:
	rm -f $(knw_dir)/*~

##### learning algorithms
trg_dir = learn

trg_cmd = cd $(trg_dir); make $@

pattern:
	$(trg_cmd)

pattern_set:
	$(trg_cmd)

h_pattern:
	$(trg_cmd)

h_pattern_set:
	$(trg_cmd)

learning:
	$(trg_cmd)

trainings: pattern pattern_set h_pattern h_pattern_set learning

clean_trainings_temp:
	rm -f $(trg_dir)/*~

#### tests
tst_dir = tests

tst_cmd = cd $(tst_dir); make $@

test_unit: unit
	$(tst_cmd)

test_synaptic: unit synaptic
	$(tst_cmd)

test_synaptics: utils
	$(tst_cmd)

test_neuron: activation neuron heavy_neuron
	$(tst_cmd)

test_layer: activation neuron layer heavy_neuron heavy_layer
	$(tst_cmd)

test_network: abstracts utils heavies
	$(tst_cmd)

test_MLP_model: abstracts utils heavies models
	$(tst_cmd)

## not implemented yet
test_hopfield_model: abstracts utils heavies models
	$(tst_cmd)

test_kohonen_model: abstracts utils heavies models
	$(tst_cmd)
## end not implemented yet

test_models: test_MLP_model #test_hopfield_model test_kohonen_model

test_MLP: abstracts utils heavies models heavy_MLP
	$(tst_cmd)

test_pattern: pattern h_pattern
	$(tst_cmd)

test_pattern_set: pattern pattern_set h_pattern h_pattern_set
	$(tst_cmd)

test_backprop: abstracts utils heavies trainings
	$(tst_cmd)

all_tests: test_neuron test_layer test_unit test_synaptic test_synaptics test_network test_models test_MLP test_pattern test_pattern_set test_backprop

dashboard: all_tests
	$(tst_cmd)

clean_tests_temp:
	rm -f $(tst_dir)/*~

##### cleaning

cleantemp: clean_abstracts_temp clean_utils_temp clean_heavies_temp clean_lights_temp clean_known_temp clean_trainings_temp clean_tests_temp
	rm -f res/*~ inc/*~

cleanobj:
	rm -f $(obj)/*.o

distclean:
	rm -f $(exe)/*.out

cleanall: cleantemp cleanobj distclean
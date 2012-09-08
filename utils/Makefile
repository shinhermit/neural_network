#VARIABLES
src= .
inc= -I. -I../inc -I../abstract -I../heavy_net
obj= ../obj
flags= -Wall -g
cc= g++

#CIBLES

all: synaptic

unit:
	$(cc) -c $(inc) $(flags) $(src)/$@.cpp
	mv $@.o $(obj)

synaptic: unit
	$(cc) -c $(inc) $(flags) $(src)/$@.cpp
	mv $@.o $(obj)

synaptics: synaptic
	$(cc) -c $(inc) $(flags) $(src)/$@.cpp
	mv $@.o $(obj)

models:
	$(cc) -c $(inc) $(flags) $(src)/$@.cpp
	mv $@.o $(obj)

funcs:
	$(cc) -c $(inc) $(flags) $(src)/$@.cpp
	mv $@.o $(obj)

activation:
	$(cc) -c $(inc) $(flags) $(src)/$@.cpp
	mv $@.o $(obj)

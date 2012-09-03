#VARIABLES
src= .
inc= -I.
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

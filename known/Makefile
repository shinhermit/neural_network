#VARIABLES
src= .
inc= -I. -I../abstract -I../inc -I../utils -I../heavy_net
obj= ../obj
flags= -Wall -g
cc= g++

#CIBLES

all: heavy_MLP

heavy_MLP:
	$(cc) -c $(inc) $(flags) $(src)/$@.cpp	
	mv $@.o $(obj)

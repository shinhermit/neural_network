#VARIABLES
src= .
inc= -I. -I../abstract -I../inc -I../utils -I../heavy_net
obj= ../obj
flags= -Wall -g #-DDEBUG
cc= g++

#CIBLES

pattern:
	$(cc) -c $(inc) $(flags) $(src)/$@.cpp
	mv $@.o $(obj)

pattern_set:
	$(cc) -c $(inc) $(flags) $(src)/$@.cpp
	mv $@.o $(obj)

h_pattern:
	$(cc) -c $(inc) $(flags) $(src)/$@.cpp
	mv $@.o $(obj)

h_pattern_set:
	$(cc) -c $(inc) $(flags) $(src)/$@.cpp
	mv $@.o $(obj)

learning:
	$(cc) -c $(inc) $(flags) $(src)/$@.cpp
	mv $@.o $(obj)

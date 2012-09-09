#VARIABLES
src= .
inc= -I. -I../abstract -I../inc -I../utils -I../heavy_net
obj= ../obj
flags= -Wall -g #-DDEBUG
cc= g++

#CIBLES

cmd = $(cc) -c $(inc) $(flags) $(src)/$@.cpp; mv $@.o $(obj)

pattern:
	$(cmd)

pattern_set:
	$(cmd)

h_pattern:
	$(cmd)

h_pattern_set:
	$(cmd)

learning:
	$(cmd)

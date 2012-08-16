#VARIABLES
src= .
inc= .
flags= -Wall -g
cc= g++

#CIBLES

neuron:
	$(cc) -c -I$(inc) $(flags) $(src)/$@.cpp

cleantemp:
	rm *~

cleanall: cleantemp
	rm *.o; rm *.out
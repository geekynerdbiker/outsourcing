OBJ = assignment.o wav-file.o

all: main util
	g++ -o assignment $(OBJ)  -lm
main: assignment.cpp
	g++ -c assignment.cpp
util: wav-file.cpp wav-file.h
	g++ -c wav-file.cpp

clean: 
	rm -f $(OBJ) assignment
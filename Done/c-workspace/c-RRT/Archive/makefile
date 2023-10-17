OBJ = rrtTester.o rrtMaker.o display.o

all: main util1 util2
	gcc -o rrtTester $(OBJ) -lX11 -L/usr/X11/lib -I/usr/X11/include -lm
main: rrtTester.c obstacles.h display.h
	gcc -c rrtTester.c
util1: rrtMaker.c obstacles.h display.h
	gcc -c rrtMaker.c
util2: display.c obstacles.h display.h
	gcc -c display.c

clean: 
	rm -f $(OBJ) rrtTester
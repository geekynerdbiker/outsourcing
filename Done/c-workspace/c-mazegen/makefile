CFLAGS = -Wall -Werror -g

all: maze mazegen

maze: maze.o
	gcc $(CFLAGS) -o maze maze.o

mazegen: mazegen.o
	gcc $(CFLAGS) -o mazegen mazegen.o

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@
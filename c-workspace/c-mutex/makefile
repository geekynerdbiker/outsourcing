CC      = gcc
CFLAGS  = -std=gnu11 -Wall -Werror
LIBS    = -lpthread

all: defrag

defrag: defrag.c
	$(CC) $(CFLAGS) defrag.c -o defrag $(LIBS)

clean:
	rm -f defrag

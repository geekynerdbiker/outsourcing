CC=g++
CFLAGS=-Wall -g
LDFLAGS=
SOURCES=main.cpp book.cpp inventory.cpp book_genre_stats.cpp hash_table.h binary_search_tree.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Assignment3

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o $(EXECUTABLE)

CXX = g++
CXXFLAGS = -Wall -std=c++17

SOURCES = Node.cpp Heap.cpp
HEADERS = Node.h Heap.h

OBJECTS = $(SOURCES:.cpp=.o)

TARGETS = main1 main2 main3

all: $(TARGETS)

main1: main1.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main2: main2.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main3: main3.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS) $(OBJECTS) *.o

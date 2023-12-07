btree: slot_header.o page.o btree.o main_btree.o
	g++ -c slot_header.cpp
	g++ -c page.cpp
	g++ -c main_btree.cpp
	g++ -c btree.cpp
	g++ -o ./btree slot_header.o page.o btree.o main_btree.o

clean:
	rm -f page
	rm -f btree
	rm -f *.o

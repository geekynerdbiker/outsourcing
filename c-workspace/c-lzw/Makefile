HEADERS = decode.h encode.h dict.h bit_io.h
OBJECTS = program.o decode.o encode.o dict.o bit_io.o

default: program

program.o: main.c $(HEADERS)
	gcc -c main.c -o program.o

decode.o: decode.c decode.h
	gcc -c decode.c -o decode.o

encode.o: encode.c encode.h
	gcc -c encode.c -o encode.o

dict.o: dict.c dict.h
	gcc -c dict.c -o dict.o

bit_io.o: bit_io.c bit_io.h
	gcc -c bit_io.c -o bit_io.o

program: $(OBJECTS)
	touch encode
	touch decode
	touch dict
	rm -f decode
	rm -f encode
	rm -f dict
	
	gcc $(OBJECTS) -o program

	ln -s program decode
	ln -s program encode

clean:
	-rm -f $(OBJECTS)
	-rm -f program
	-rm -f decode
	-rm -f encode
	-rm -f dict
	-rm -f dictionary.dat

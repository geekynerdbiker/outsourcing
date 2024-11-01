main	:	main.o	KISA_SEED_CBC.o
	gcc	-o main	main.o	KISA_SEED_CBC.o
	
main.o	:	main.c
	gcc	-c -o	main.o	main.c
	
KISA_SEED_CBC.o	:	KISA_SEED_CBC.c
	gcc	-c	-o	KISA_SEED_CBC.o	KISA_SEED_CBC.c
	
clean	:
	rm	*.o	main

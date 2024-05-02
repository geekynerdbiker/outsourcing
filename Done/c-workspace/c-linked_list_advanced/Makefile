CC	=	gcc
CFLAGS	=	-W -Wall -O2
LDFLAGS	=	-lm

project1 	:	project1_main.c linked_list.h linked_list.c
	$(CC)   $(CFLAGS)       -o      $@      $^      $(LDFLAGS)
	
clean   :
	@rm     -rf     *.o     mst
	@rm 		-rf 		*.exe 	mst
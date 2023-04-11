#include <stdio.h>
#include <unistd.h>

int main(void) {
	pid_t pid;

	if ((pid = fork() == 0))
		printf("Child: pid %d pgrp %d", getpid(), getpgrp());
	else {
		printf("Parent: pid %d pgrp %d", getpid(), getpgrp());
		while(1);
	}
}

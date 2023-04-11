#include <stdio.h>
#include <unistd.h>

int main(void) {
	pid_t pid;

	if ((pid = fork() == 0)) {
		printf("Child: pid %d pgrp %d\n", getpid(), getpgrp());
		printf("Running child process...\n");
		sleep(10);
		printf("Child process done\n");
	}
	else {
		printf("Parent: pid %d pgrp %d\n", getpid(), getpgrp());
		printf("Running parent process...\n");
		sleep(10);
		printf("Parent process done\n");
	}
}

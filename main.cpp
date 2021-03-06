#include <unistd.h> // fork pipe
#include <string.h> // strlen
#include <stdio.h> // printf
#include <stdlib.h> // exit
#define MAX 256
#define RD_END 0
#define WR_END 1

int main() {
	// create a pipe
	int fd[2];
	if (pipe(fd) < 0) {
		printf("cannot create a pipe.\n");
		exit(1);
	}

	pid_t pid = fork();
	if (pid < 0) {
		printf("cannot fork()\n");
		exit(1);
	} else if (pid == 0) { // child process
		close(fd[RD_END]);
		char data[MAX];
		while (true) {
			printf("CHILD: Enter a message (or quit): ");
			fgets(data, MAX, stdin); // reads with '\n'
			data[strlen(data) - 1] = '\0'; // remove '\n'
			write(fd[WR_END], data, strlen(data) + 1);
			if (strcmp(data, "quit") == 0)
				break;
		}
		exit(0);

	} else { // parent process
		close(fd[WR_END]);
		char data[MAX];
		while (true) {
			read(fd[RD_END], data, sizeof(data));
			printf("\t| PARENT received: %s\n", data);
			if (strcmp(data, "quit") == 0)
				break;
		}
	}
}
#include <iostream>
using namespace std;
#include <unistd.h>
#include <string.h>
#define MAX 256

void clean(char *);

int main() {
	// create a pipe
	int fd[2];
	if (pipe(fd) < 0) {
		cerr << "cannot create a pipe." << endl;
		exit(1);
	}

	pid_t pid = fork();
	if (pid < 0) {
		cerr << "cannot fork()" << endl;
		exit(1);
	} else if (pid == 0) { // child process
		string data;
		while (true) {
			cout << "Enter a word: ";	
			getline(cin, data);
			const char* c_string = data.c_str();
			write(fd[1], c_string, strlen(c_string) + 1);
		}
		exit(0);

	} else { // parent process
		char data[MAX];
		while (true) {
			read(fd[0], data, sizeof(data));
			string rd_string(data);
			cout << "\n\t\t\tMessage received: " << data << endl;
		}

	}
}

void clean(char* data) {
	for (int i = 0; i < MAX; i++) {
		data[i] = '\0';
	}
}
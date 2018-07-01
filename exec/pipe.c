#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[], char **envp) {
	pid_t pid, cpid;
	int exit_status;
	int fdin[2], fdout[2], fderr[2];
	int j;
	char c;
	
	if (pipe(fdin) < 0) {
		perror("pipe");
		exit(errno);
	}
	
	if (pipe(fdout) < 0) {
		perror("pipe");
		exit(errno);
	}
	
	if (pipe(fderr) < 0) {
		perror("pipe");
		exit(errno);
	}
	
	pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(errno);
	} else if (!pid) {
		dup2(fdin[0], 0);
		dup2(fdout[1], 1);
		dup2(fderr[1], 2);
		for (j = 0; ; j++) {
			fprintf(stderr, "piped message %d\n", j);
			fflush(stderr);
			sleep(1);
		}
	} else {
		while (read(fderr[0], &c, 1) > 0)
			(void)write(1, &c, 1);
		(void)wait(&exit_status);
		exit(exit_status);
	}
	
	return 0;
}


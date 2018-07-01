#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[], char **envp) {
	pid_t pid, cpid;
	int exit_status;
	char *arg[] = {
		"/usr/bin/env",
		NULL
	};
	char *env[] = {
		"HOME=/tmp",
		"LANG=en_US.UTF-8",
		"TERM=xterm",
		NULL
	};
	
	pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(errno);
	} else if (!pid) {
		printf("child pid = %d, parent pid = %d\n", getpid(), getppid());
		if (execve(arg[0], arg, env) < 0) {
			perror("execve");
			exit(errno);
		}
	} else {
		cpid = wait(&exit_status);
		printf("child pid = %d exited, exit status = %d\n", cpid, exit_status);
		exit(exit_status);
	}
	
	return 0;
}


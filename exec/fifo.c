#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[], char **envp) {
	pid_t pid, cpid;
	int exit_status;
	int fd;
	int j;
	char c;
	
	pid = fork();
	if (pid < 0) {
		perror("fork");
		exit(errno);
	} else if (!pid) {
		fd = open("fifo", O_WRONLY);
		dup2(fd, 2);
		close(fd);
		for (j = 0; j < 20; j++) {
			fprintf(stderr, "piped message %d\n", j);
			fflush(stderr);
			sleep(1);
		}
		exit(0);
	} else {
		fd = open("fifo", O_RDONLY);
		while (read(fd, &c, 1) > 0)
			(void)write(1, &c, 1);
		close(fd);
		(void)wait(&exit_status);
		exit(exit_status);
	}
	
	return 0;
}


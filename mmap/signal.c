#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sighnd(int sig) {
	printf("Caught signal %d\n", sig);
	fflush(stdout);
	signal(SIGTERM, &sighnd);
	return;
}

int main(int argc, char *argv[]) {
	signal(SIGTERM, &sighnd);
	while (1)
		sigpause(SIGTERM);
	return 0;
}


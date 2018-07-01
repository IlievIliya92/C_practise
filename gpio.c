#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

const char *paths[8] = {
	"/sys/class/gpio/gpio36/value",
	"/sys/class/gpio/gpio32/value",
	"/sys/class/gpio/gpio61/value",
	"/sys/class/gpio/gpio33/value",
	"/sys/class/gpio/gpio54/value",
	"/sys/class/gpio/gpio34/value",
	"/sys/class/gpio/gpio55/value",
	"/sys/class/gpio/gpio35/value"
};

static int fd[8];

static int digit_left[16][8] = {
	{ 1, 1, 1, 0, 1, 0, 1, 1 }, /* 0 */
	{ 0, 0, 1, 0, 0, 0, 0, 1 }, /* 1 */
	{ 1, 1, 0, 0, 0, 1, 1, 1 }, /* 2 */
	{ 0, 1, 1, 0, 0, 1, 1, 1 }, /* 3 */
	{ 0, 0, 1, 0, 1, 1, 0, 1 }, /* 4 */
	{ 0, 1, 1, 0, 1, 1, 1, 0 }, /* 5 */
	{ 1, 1, 1, 0, 1, 1, 1, 0 }, /* 6 */
	{ 0, 0, 1, 0, 0, 0, 1, 1 }, /* 7 */
	{ 1, 1, 1, 0, 1, 1, 1, 1 }, /* 8 */
	{ 0, 1, 1, 0, 1, 1, 1, 1 }, /* 9 */
	{ 1, 0, 1, 0, 1, 1, 1, 1 }, /* A */
	{ 1, 1, 1, 0, 1, 1, 0, 0 }, /* b */
	{ 1, 1, 0, 0, 1, 0, 1, 0 }, /* C */
	{ 1, 1, 1, 0, 0, 1, 0, 1 }, /* d */
	{ 1, 1, 0, 0, 1, 1, 1, 0 }, /* E */
	{ 1, 0, 0, 0, 1, 1, 1, 0 } /* F */
};

void set_gpio(int fd, int _val) {
	char val = _val ? '1' : '0';
	
	(void)write(fd, &val, 1);
	(void)lseek(fd, 0, SEEK_SET);
	return;
}

int main(int argc, char *argv[]) {
	int i, j;
	
	for (j = 0; j < 8; j++)
		fd[j] = open(paths[j], O_RDWR);
	
	while (1) {
		for (i = 0; i < 16; i++) {
			for (j = 0; j < 8; j++) {
				set_gpio(fd[j], digit_left[i][j]);
			}
			sleep(1);
		}
	}
	
	for (j = 0; j < 8; j++) {
		set_gpio(fd[j], 0);
		close(fd[j]);
	}
	
	return 0;
}

#include <stdio.h>

void setpixel(unsigned char *display, int M, int N, int i, int j, unsigned char value);
unsigned char getpixel(unsigned char *display, int M, int N, int i, int j);

/*
#define ROWS 32
#define COLUMNS 64
*/

enum {
	ROWS = 32,
	COLUMNS = 64
};

int main(void) {
	unsigned char display[ROWS * COLUMNS], pixel;
	int i, j;
	
	for (i = 0; i < ROWS * COLUMNS; i++)
		display[i] = 0u;
	
	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLUMNS; j++)
			if (i == j) setpixel(display, ROWS, COLUMNS, i, j, 1u);
	
	for (i = 0; i < ROWS; i++) {
		printf("|");
		for (j = 0; j < COLUMNS; j++) {
			pixel = getpixel(display, ROWS, COLUMNS, i, j);
			printf("%c", pixel ? '*' : ' ');
		}
		printf("|\n");
	}
	
	return 0;
}

void setpixel(unsigned char *display, int M, int N, int i, int j, unsigned char value) {
	if ((i < 0) || (i >= M)) return;
	if ((j < 0) || (j >= N)) return;
	display[i * N + j] = value;
	return;
}

unsigned char getpixel(unsigned char *display, int M, int N, int i, int j) {
	if ((i < 0) || (i >= M)) return 0u;
	if ((j < 0) || (j >= N)) return 0u;
	return display[i * N + j];
}


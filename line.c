#include <stdio.h>
#include <stdlib.h>

void setpixel(unsigned char *display, int M, int N, int i, int j, unsigned char value);
unsigned char getpixel(unsigned char *display, int M, int N, int i, int j);
void bresenham(int x0, int y0, int x1, int y1, unsigned char *display);

enum {
	ROWS = 20,
	COLUMNS = 20
};

int main(void) {
	unsigned char display[ROWS * COLUMNS], pixel;
	int i, j;
	
	for (i = 0; i < ROWS * COLUMNS; i++)
	    display[i] = 0u;
	
	bresenham(0, 0, 0, 30, display);
	
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

void bresenham(int x0, int y0, int x1, int y1, unsigned char *display) {

	if (x0 > ROWS || x1 > ROWS) {
		fprintf(stderr, "ERROR\nROWS are out of range!\nRange:\nROWS: <%d\n", ROWS);		
		exit(1); 
	}

	if (y0 > COLUMNS || y1 > COLUMNS) {
		fprintf(stderr, "ERROR\nCOLUMNSS are out of range!\nRange:\nCOLUMNS: <%d\n", COLUMNS);		
		exit(1); 
	}

	int dx = abs(x1 - x0);
	int sx = (x0 < x1) ? 1 : -1;
	int dy = abs(y1 - y0);
	int sy = (y0 < y1) ? 1 : -1;  
	int err = ( (dx > dy) ? dx : -dy) / 2;
	int err2;
 
  while(1) {
	setpixel(display, ROWS, COLUMNS, x0, y0, 255);
	if (x0 == x1 && y0 == y1) 
		break;

		err2 = err;
		if (err2 > -dx) { 
			err -= dy;
			x0 += sx; 
		}
		if (err2 < dy) { 
			err += dx;
			y0 += sy; 
		}
	}

	return;
}


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "internal/display.h"
#include "display_object.h"

void *display_create(unsigned char *_d, int M, int N) {
	display *d = (display *)malloc(sizeof (display));
	
	if (!d) return NULL;
	
	d->M = M;
	d->N = N;
	d->display = _d;
	
	return (void *)d;
}

void display_destroy(void *d) {
	free(d);
	return;
}

void display_setpix(void *_d, int i, int j, unsigned char  value) {
	display *d = (display *)_d;
	
	if ((i < 0) || (i >= d->M)) return;
	if ((j < 0) || (j >= d->N)) return;
	d->display[i * d->N + j] = value;
	return;	
}

unsigned char display_getpix(void *_d, int i, int j) {
	display *d = (display *)_d;

	if ((i < 0) || (i >= d->M)) return 0u;
	if ((j < 0) || (j >= d->N)) return 0u;
	return d->display[i * d->N + j];
}

void display_brez_line(void *_d, int x0, int y0, int x1, int y1, unsigned char value) {
	int dx = abs(x1 - x0);
	int sx = (x0 < x1) ? 1 : -1;
	int dy = abs(y1 - y0);
	int sy = (y0 < y1) ? 1 : -1;  
	int err = ((dx > dy) ? dx : -dy) / 2;
	int err2;
 
	while(1) {
		display_setpix(_d, x0, y0, value);
		if ((x0 == x1) && (y0 == y1)) break;
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

void display_brez_c(void *_d, int x, int y, int r, unsigned char value) {
	int x0 = r - 1;
	int y0 = 0;
	int dx = 1;
	int dy = 1;
	int err = dx -(r << 1);
	
	while (x >= y) {
		display_setpix(_d, x + x0, y + y0, value);
		display_setpix(_d, x + x0, y + y0, value);
		display_setpix(_d, x - x0, y + y0, value);
		display_setpix(_d, x - x0, y + y0, value);
		display_setpix(_d, x - x0, y - y0, value);
		display_setpix(_d, x - x0, y - y0, value);
		display_setpix(_d, x + x0, y - y0, value);
		display_setpix(_d, x + x0, y - y0, value);

		if (err <= 0) {
			y0++;
			err += dy;
			dy += 2;
		}
		if (err > 0) {
			x0--;
			dx += 2;
			err += (-r << 1) + dx;
		} 
	}
	
	return;
}



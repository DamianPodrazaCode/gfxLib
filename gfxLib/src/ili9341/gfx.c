#include "gfx.h"
#include "main.h"
#include "ili9341.h"
#include <stdlib.h>

#define swap(a, b) { int16_t t = a; a = b; b = t; }
void lcdLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
	// Bresenham's algorithm - thx wikpedia
	int16_t steep = abs(y2 - y1) > abs(x2 - x1);
	if (steep > 0) {
		swap(x1, y1);
		swap(x2, y2);
	}
	if (x1 > x2) {
		swap(x1, x2);
		swap(y1, y2);
	}
	int16_t dx, dy;
	dx = x2 - x1;
	dy = abs(y2 - y1);
	int16_t err = dx / 2;
	int16_t ystep;
	if (y1 < y2) {
		ystep = 1;
	} else {
		ystep = -1;
	}
	for (; x1 <= x2; x1++) {
		if (steep) {
			lcdDrawPixel(y1, x1, color);
		} else {
			lcdDrawPixel(x1, y1, color);
		}
		err -= dy;
		if (err < 0) {
			y1 += ystep;
			err += dx;
		}
	}
}


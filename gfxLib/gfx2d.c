#include "gfx.h"
#include <math.h>

void gfx2d_line(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint16_t color) {

// 557
//	register int dx = ABS(x1 - x0);
//	register int sx = (x0 < x1) ? 1 : -1;
//	register int dy = -ABS(y1 - y0);
//	register int sy = (y0 < y1) ? 1 : -1;
//	register int error = dx + dy;
//	register int e2;
//	register int x = x0;
//	register int y = y0;
//
//	while ((x != x1) || (y != y1)) {
//		drawPixel(x, y, color);
//		e2 = error << 1;
//		if (e2 >= dy) {
//			error = error + dy;
//			x = x + sx;
//		}
//		if (e2 <= dx) {
//			error = error + dx;
//			y = y + sy;
//		}
//	}

// 549
//	register int x = x0;
//	register int y = y0;
//	register int e = 0;
//	register int kx = (x <= x1) ? 1 : -1;
//	register int ky = (y <= y1) ? 1 : -1;
//	register int dx = ABS(x1 - x);
//	register int dy = ABS(y1 - y);
//
//	if (dx >= dy) {
//		e = dx >> 1;
//		do {
//			drawPixel(x, y, color);
//			x = x + kx;
//			e = e - dy;
//			if (e < 0) {
//				y = y + ky;
//				e = e + dx;
//			}
//		} while (x != x1);
//	} else {
//		e = dy >> 1;
//		do {
//			drawPixel(x, y, color);
//			y = y + ky;
//			e = e - dx;
//			if (e < 0) {
//				x = x + kx;
//				e = e + dy;
//			}
//		} while (y != y1);
//	}

//	register int dx = x1 - x0;
//	register int dy = y1 - y0;
//	register int stepI = dx / dy;
//	register int stepM = dx % dy;
//	register int e = dx;
//
//	do {
//		drawPixel(x0, y0++, color);
//		stepI = e / dy;
//		stepM = e % dy;
//		x0 = x0 + stepI;
//		e = dx + stepM;
//	} while (y0 != y1);

//	register int x = x0;
//	register int y = y0;
//	register int e = 0;
//	register int kx = (x <= x1) ? 1 : -1;
//	register int ky = (y <= y1) ? 1 : -1;
//	register int dx = ABS(x1 - x);
//	register int dy = ABS(y1 - y);
//
//	if (dx >= dy) {
//		e = dx >> 1;
//		do {
//			drawPixel(x, y, color);
//			x = x + kx;
//			e = e - dy;
//			if (e < 0) {
//				y = y + ky;
//				e = e + dx;
//			}
//		} while (x != x1);
//	} else {
//		e = dy >> 1;
//		do {
//			drawPixel(x, y, color);
//			y = y + ky;
//			e = e - dx;
//			if (e < 0) {
//				x = x + kx;
//				e = e + dy;
//			}
//		} while (y != y1);
//	}

}

void gfx2d_triangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint16_t color) {
	gfx2d_line(x0, y0, x1, y1, color);
	gfx2d_line(x0, y0, x2, y2, color);
	gfx2d_line(x2, y2, x1, y1, color);
}

void gfx2d_rect(int32_t x, int32_t y, int32_t width, int32_t height, uint16_t color) {
}
void gfx2d_roundRect(int32_t x, int32_t y, int32_t width, int32_t height, uint32_t r, uint16_t color) {
}
void gfx2d_circle(int32_t x, int32_t y, uint32_t r, uint16_t color) {
}
void gfx2d_polygon(gfxPoint *points, uint32_t pointCount, uint16_t color) {
}
void gfx2d_ellipse(int32_t Xpos, int32_t Ypos, uint32_t XRadius, uint32_t YRadius, uint16_t color) {
}

typedef struct {
	int32_t dx;
	int32_t sx;
	int32_t dy;
	int32_t sy;
	int32_t error;
	int32_t e2;
	int32_t x;
	int32_t y;
	int32_t xTemp;
	int32_t yTemp;
} lineComplex_t;

static void lineInit(lineComplex_t *line, int32_t *x0, int32_t *y0, int32_t *x1, int32_t *y1) {
	line->dx = ABS(*x1 - *x0);
	line->sx = (*x0 < *x1) ? 1 : -1;
	line->dy = -ABS(*y1 - *y0);
	line->sy = (*y0 < *y1) ? 1 : -1;
	line->error = line->dx + line->dy;
	line->e2 = 0;
	line->xTemp = *x0;
	line->yTemp = *y0;
}

static void lineStep(lineComplex_t *line) {
	line->x = line->xTemp;
	line->y = line->yTemp;
	line->e2 = line->error << 1;
	if (line->e2 >= line->dy) {
		line->error = line->error + line->dy;
		line->xTemp = line->xTemp + line->sx;
	}
	if (line->e2 <= line->dx) {
		line->error = line->error + line->dx;
		line->yTemp = line->yTemp + line->sy;
	}
}

void gfx2d_fillTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint16_t color) {

	// sortowanie wierzchołków
	if (y0 > y1) {
		SWAP(y0, y1);
		SWAP(x0, x1);
	}
	if (y0 > y2) {
		SWAP(y0, y2);
		SWAP(x0, x2);
	}
	if (y1 > y2) {
		SWAP(y1, y2);
		SWAP(x1, x2);
	}

	int x3 = (int) (x0 + ((float) (y1 - y0) / (float) (y2 - y0)) * (x2 - x0));
	int y3 = y1;

	//gfx2d_line(x0, y0, x1, y1, 0x07FF);

	lineComplex_t line1, line2, line3;

	lineInit(&line1, &x0, &y0, &x1, &y1);
	lineInit(&line2, &x0, &y0, &x2, &y2);
	while ((line1.x != x1) || (line1.y != y1)) {
		lineStep(&line1);
		drawPixel(line1.x, line1.y, color);
		if (line2.y <= line1.y) {
			lineStep(&line2);
			drawPixel(line2.x, line2.y, color);
		}
	}

//		gfx2d_line(x0, y0, x1, y1, 0x07FF);
//		gfx2d_line(x0, y0, x3, y3, 0x07FF);
//		gfx2d_line(x1, y1, x3, y3, 0x001F);
//
//		gfx2d_line(x2, y2, x1, y1, 0x07FF);
//		gfx2d_line(x2, y2, x3, y3, 0x07FF);

//	int16_t t1x, t2x, y, minx, maxx, t1xp, t2xp;
//	uint8_t changed1 = 0;
//	uint8_t changed2 = 0;
//	int16_t signx1, signx2, dx1, dy1, dx2, dy2;
//	uint32_t e1, e2;
//	uint32_t i, j;
//
//	if (y0 > y1) {
//		SWAP(y0, y1);
//		SWAP(x0, x1);
//	}
//	if (y0 > y2) {
//		SWAP(y0, y2);
//		SWAP(x0, x2);
//	}
//	if (y1 > y2) {
//		SWAP(y1, y2);
//		SWAP(x1, x2);
//	}
//
//	t1x = t2x = x0;
//	y = y0;
//
//	dx1 = x1 - x0;
//	if (dx1 < 0) {
//		dx1 = -dx1;
//		signx1 = -1;
//	} else
//		signx1 = 1;
//	dy1 = y1 - y0;
//
//	dx2 = x2 - x0;
//	if (dx2 < 0) {
//		dx2 = -dx2;
//		signx2 = -1;
//	} else
//		signx2 = 1;
//	dy2 = y2 - y0;
//
//	if (dy1 > dx1) {
//		SWAP(dx1, dy1);
//		changed1 = 0x01;
//	}
//	if (dy2 > dx2) {
//		SWAP(dy2, dx2);
//		changed2 = 0x01;
//	}
//
//	e2 = dx2 >> 1;
//
//	if (y0 == y1)
//		goto next;
//	e1 = dx1 >> 1;
//
//	for (i = 0; i < dx1;) {
//		t1xp = 0;
//		t2xp = 0;
//		if (t1x < t2x) {
//			minx = t1x;
//			maxx = t2x;
//		} else {
//			minx = t2x;
//			maxx = t1x;
//		}
//
//		while (i < dx1) {
//			i++;
//			e1 += dy1;
//			while (e1 >= dx1) {
//				e1 -= dx1;
//				if (changed1)
//					t1xp = signx1;
//				else
//					goto next1;
//			}
//			if (changed1)
//				break;
//			else
//				t1x += signx1;
//		}
//		next1: while (1) {
//			e2 += dy2;
//			while (e2 >= dx2) {
//				e2 -= dx2;
//				if (changed2)
//					t2xp = signx2;
//				else
//					goto next2;
//			}
//			if (changed2)
//				break;
//			else
//				t2x += signx2;
//		}
//		next2: if (minx > t1x)
//			minx = t1x;
//		if (minx > t2x)
//			minx = t2x;
//		if (maxx < t1x)
//			maxx = t1x;
//		if (maxx < t2x)
//			maxx = t2x;
//		drawHLine(minx, maxx, y, color);
//		if (!changed1)
//			t1x += signx1;
//		t1x += t1xp;
//		if (!changed2)
//			t2x += signx2;
//		t2x += t2xp;
//		y += 1;
//		if (y == y1)
//			break;
//
//	}
//	next: dx1 = x2 - x1;
//	if (dx1 < 0) {
//		dx1 = -dx1;
//		signx1 = -1;
//	} else
//		signx1 = 1;
//	dy1 = y2 - y1;
//	t1x = x1;
//
//	if (dy1 > dx1) {
//		SWAP(dy1, dx1);
//		changed1 = 0x01;
//	} else
//		changed1 = 0x00;
//
//	e1 = dx1 >> 1;
//
//	for (j = 0; j <= dx1; j++) {
//		t1xp = 0;
//		t2xp = 0;
//		if (t1x < t2x) {
//			minx = t1x;
//			maxx = t2x;
//		} else {
//			minx = t2x;
//			maxx = t1x;
//		}
//		while (j < dx1) {
//			e1 += dy1;
//			while (e1 >= dx1) {
//				e1 -= dx1;
//				if (changed1) {
//					t1xp = signx1;
//					break;
//				} else
//					goto next3;
//			}
//			if (changed1)
//				break;
//			else
//				t1x += signx1;
//			if (j < dx1)
//				j++;
//		}
//		next3: while (t2x != x2) {
//			e2 += dy2;
//			while (e2 >= dx2) {
//				e2 -= dx2;
//				if (changed2)
//					t2xp = signx2;
//				else
//					goto next4;
//			}
//			if (changed2)
//				break;
//			else
//				t2x += signx2;
//		}
//		next4:
//
//		if (minx > t1x)
//			minx = t1x;
//		if (minx > t2x)
//			minx = t2x;
//		if (maxx < t1x)
//			maxx = t1x;
//		if (maxx < t2x)
//			maxx = t2x;
//		drawHLine(minx, maxx, y, color);
//		if (!changed1)
//			t1x += signx1;
//		t1x += t1xp;
//		if (!changed2)
//			t2x += signx2;
//		t2x += t2xp;
//		y += 1;
//		if (y > y2)
//			return;
//	}

}
void gfx2d_fillRect(int32_t x, int32_t y, int32_t width, int32_t height, uint16_t color) {
}
void gfx2d_fillRoundRect(int32_t x, int32_t y, int32_t width, int32_t height, uint32_t r, uint16_t color) {
}
void gfx2d_fillCircle(int32_t x, int32_t y, uint32_t r, uint16_t color) {
}
void gfx2d_fillPolygon(gfxPoint *points, uint32_t pointCount, uint16_t color) {
}
void gfx2d_fillEllipse(int32_t Xpos, int32_t Ypos, uint32_t XRadius, uint32_t YRadius, uint16_t color) {
}

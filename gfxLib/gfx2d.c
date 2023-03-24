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
	register int x = x0;
	register int y = y0;
	register int e = 0;
	register int kx = (x <= x1) ? 1 : -1;
	register int ky = (y <= y1) ? 1 : -1;
	register int dx = ABS(x1 - x);
	register int dy = ABS(y1 - y);

	if (dx >= dy) {
		e = dx >> 1;
		do {
			drawPixel(x, y, color);
			x = x + kx;
			e = e - dy;
			if (e < 0) {
				y = y + ky;
				e = e + dx;
			}
		} while (x != x1);
	} else {
		e = dy >> 1;
		do {
			drawPixel(x, y, color);
			y = y + ky;
			e = e - dx;
			if (e < 0) {
				x = x + kx;
				e = e + dy;
			}
		} while (y != y1);
	}

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
	int32_t e;
	int32_t kx;
	int32_t ky;
	int32_t dx;
	int32_t dy;
	int32_t x;
	int32_t y;
} lineComplex_t;

static inline void lineInit(lineComplex_t *line, int32_t *x0, int32_t *y0, int32_t *x1, int32_t *y1) {
	line->e = 0;
	line->kx = (*x0 <= *x1) ? 1 : -1;
	line->ky = (*y0 <= *y1) ? 1 : -1;
	line->dx = ABS(*x1 - *x0);
	line->dy = ABS(*y1 - *y0);
	line->x = *x0;
	line->y = *y0;

	if (line->dx >= line->dy)
		line->e = line->dx >> 1;
	else
		line->e = line->dy >> 1;
}

static inline void lineStep(lineComplex_t *line) {
	if (line->dx >= line->dy) {
		do {
			line->x += line->kx;
			line->e -= line->dy;
			if (line->e < 0) {
				line->y += line->ky;
				line->e += line->dx;
				break;
			}
		} while (1);
	} else {
		line->y += line->ky;
		line->e -= line->dx;
		if (line->e < 0) {
			line->x += line->kx;
			line->e += line->dy;
		}
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

	lineComplex_t line1, line2, line3;

	lineInit(&line1, &x0, &y0, &x1, &y1);
	lineInit(&line2, &x0, &y0, &x2, &y2);

	for (int i = y0; i < y1; i++) {
		drawHLine(line1.x, line2.x, line2.y, color);
		lineStep(&line1);
		lineStep(&line2);
	}
	lineInit(&line3, &x1, &y1, &x2, &y2);
	for (int i = y1; i < y2; i++) {
		drawHLine(line3.x, line2.x, line2.y, color);
		lineStep(&line2);
		lineStep(&line3);
	}
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

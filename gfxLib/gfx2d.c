#include "gfx.h"
#include <math.h>

void gfx2d_line(gfx2dPoint_t A, gfx2dPoint_t B, uint16_t color) {
	if ((A.x != B.x) && (A.y != B.y)) {
		register int32_t x = A.x;
		register int32_t y = A.y;
		register int32_t kx = (x <= B.x) ? 1 : -1;
		register int32_t ky = (y <= B.y) ? 1 : -1;
		register uint32_t dx = ABS(B.x - x);
		register uint32_t dy = ABS(B.y - y);
		register int32_t e;

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
			} while (x != B.x);
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
			} while (y != B.y);
		}
	} else {
		drawPixel(A.x, A.y, color);
	}
}

void gfx2d_triangle(gfx2dPoint_t A, gfx2dPoint_t B, gfx2dPoint_t C, uint16_t color) {
	gfx2d_line(A, B, color);
	gfx2d_line(A, C, color);
	gfx2d_line(C, B, color);
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

static inline void lineInit(lineComplex_t *pline, gfx2dPoint_t *pA, gfx2dPoint_t *pB) {
	pline->e = 0;
	pline->kx = (pA->x <= pB->x) ? 1 : -1;
	pline->ky = (pA->y <= pB->y) ? 1 : -1;
	pline->dx = ABS(pB->x - pA->x);
	pline->dy = ABS(pB->y - pA->y);
	pline->x = pA->x;
	pline->y = pA->y;

	if (pline->dx >= pline->dy)
		pline->e = pline->dx >> 1;
	else
		pline->e = pline->dy >> 1;
}

static inline void lineStep(lineComplex_t *pline) {
	if (pline->dx >= pline->dy) {
		do {
			pline->x += pline->kx;
			pline->e -= pline->dy;
			if (pline->e < 0) {
				pline->y += pline->ky;
				pline->e += pline->dx;
				break;
			}
		} while (1);
	} else {
		pline->y += pline->ky;
		pline->e -= pline->dx;
		if (pline->e < 0) {
			pline->x += pline->kx;
			pline->e += pline->dy;
		}
	}
}

void gfx2d_fillTriangle(gfx2dPoint_t A, gfx2dPoint_t B, gfx2dPoint_t C, uint16_t color) {

	// sortowanie wierzchołków
	if (A.y > B.y) {
		SWAP(A.y, B.y);
		SWAP(A.x, B.x);
	}
	if (A.y > C.y) {
		SWAP(A.y, C.y);
		SWAP(A.x, C.x);
	}
	if (B.y > C.y) {
		SWAP(B.y, C.y);
		SWAP(B.x, C.x);
	}

	lineComplex_t line1, line2, line3;

	lineInit(&line1, &A, &B);
	lineInit(&line2, &A, &C);

	for (int i = A.y; i < B.y; i++) {
		drawHLine(line1.x, line2.x, line2.y, color);
		lineStep(&line1);
		lineStep(&line2);
	}
	lineInit(&line3, &B, &C);
	for (int i = B.y; i < C.y; i++) {
		drawHLine(line3.x, line2.x, line2.y, color);
		lineStep(&line2);
		lineStep(&line3);
	}
}

void gfx2d_rect(gfx2dPoint_t A, gfx2dSize_t size, uint16_t color) {
	drawHLine(A.x, A.x + size.w, A.y, color);
	drawHLine(A.x, A.x + size.w, A.y + size.h, color);
	drawVLine(A.x, A.y, A.y + size.h, color);
	drawVLine(A.x + size.w, A.y, A.y + size.h, color);
}

void gfx2d_fillRect(gfx2dPoint_t A, gfx2dSize_t size, uint16_t color) {
	int32_t Bx = A.x + size.w;
	for (int i = 0; i < size.h; i++)
		drawHLine(A.x, Bx, A.y + i, color);
}

void gfx2d_roundRect(gfx2dPoint_t A, gfx2dSize_t size, uint32_t radius, uint16_t color) {
}
void gfx2d_fillRoundRect(gfx2dPoint_t A, gfx2dSize_t size, uint32_t radius, uint16_t color) {
}

void gfx2d_circle(gfx2dPoint_t A, uint32_t radius, uint16_t color) {

	int32_t x = 0, y = radius;
	int32_t e = 0, e1, e2;

	while (x <= y) {
		drawPixel(x + A.x, y + A.y, color);
		drawPixel(y + A.x, -x + A.y, color);
		drawPixel(-x + A.x, -y + A.y, color);
		drawPixel(-y + A.x, x + A.y, color);
		drawPixel(y + A.x, x + A.y, color);
		drawPixel(x + A.x, -y + A.y, color);
		drawPixel(-y + A.x, -x + A.y, color);
		drawPixel(-x + A.x, y + A.y, color);
		e1 = e + (x << 1) + 1;
		e2 = e1 - (y << 1) + 1;
		x++;
		if (e1 + e2 >= 0) {
			e = e2;
			y--;
		} else
			e = e1;
	}
}

void gfx2d_fillCircle(gfx2dPoint_t A, uint32_t radius, uint16_t color) {
}

void gfx2d_ellipse(gfx2dPoint_t A, gfx2dSize_t size, uint16_t color) {
}
void gfx2d_fillEllipse(gfx2dPoint_t A, gfx2dSize_t size, uint16_t color) {
}

void gfx2d_polygon(gfx2dPoint_t *pPoint, uint32_t pointCount, uint16_t color) {
}
void gfx2d_fillPolygon(gfx2dPoint_t *pPoint, uint32_t pointCount, uint16_t color) {
}

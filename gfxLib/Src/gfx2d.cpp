#include <gfx.h>
#include <math.h>

void Gfx::line_2d(gfx2dPoint_t A, gfx2dPoint_t B, uint16_t color) {
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

void Gfx::triangle_2d(gfx2dPoint_t A, gfx2dPoint_t B, gfx2dPoint_t C, uint16_t color) {
	line_2d(A, B, color);
	line_2d(A, C, color);
	line_2d(C, B, color);
}

inline void Gfx::lineInit_2d(line2dComplex_t *pline, gfx2dPoint_t *pA, gfx2dPoint_t *pB) {
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

inline void Gfx::lineStep_2d(line2dComplex_t *pline) {
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

void Gfx::fillTriangle_2d(gfx2dPoint_t A, gfx2dPoint_t B, gfx2dPoint_t C, uint16_t color) {

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

	line2dComplex_t line1, line2, line3;

	lineInit_2d(&line1, &A, &B);
	lineInit_2d(&line2, &A, &C);

	for (int i = A.y; i < B.y; i++) {
		drawHLine(line1.x, line2.x, line2.y, color);
		lineStep_2d(&line1);
		lineStep_2d(&line2);
	}
	lineInit_2d(&line3, &B, &C);
	for (int i = B.y; i < C.y; i++) {
		drawHLine(line3.x, line2.x, line2.y, color);
		lineStep_2d(&line2);
		lineStep_2d(&line3);
	}
}

void Gfx::rect_2d(gfx2dPoint_t A, gfx2dSize_t size, uint16_t color) {
	drawHLine(A.x, A.x + size.w, A.y, color);
	drawHLine(A.x, A.x + size.w, A.y + size.h, color);
	drawVLine(A.x, A.y, A.y + size.h, color);
	drawVLine(A.x + size.w, A.y, A.y + size.h, color);
}

void Gfx::fillRect_2d(gfx2dPoint_t A, gfx2dSize_t size, uint16_t color) {
	int32_t Bx = A.x + size.w;
	for (int i = 0; i < size.h; i++)
		drawHLine(A.x, Bx, A.y + i, color);
}

inline void Gfx::roundHelper_2d(gfx2dPoint_t A, uint32_t radius, uint32_t side, uint16_t color) {
	int32_t x = 0, y = radius;
	int32_t e = 0, e1, e2;
	while (x <= y) {
		if (side == 0) {
			drawPixel(-x + A.x, -y + A.y, color);
			drawPixel(-y + A.x, -x + A.y, color);
		}
		if (side == 1) {
			drawPixel(y + A.x, -x + A.y, color);
			drawPixel(x + A.x, -y + A.y, color);
		}
		if (side == 2) {
			drawPixel(x + A.x, y + A.y, color);
			drawPixel(y + A.x, x + A.y, color);
		}
		if (side == 3) {
			drawPixel(-y + A.x, x + A.y, color);
			drawPixel(-x + A.x, y + A.y, color);
		}
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

void Gfx::roundRect_2d(gfx2dPoint_t A, gfx2dSize_t size, uint32_t radius, uint16_t color) {
	drawHLine(A.x + radius, A.x + size.w - radius, A.y, color);
	drawHLine(A.x + radius, A.x + size.w - radius, A.y + size.h, color);
	drawVLine(A.x, A.y + radius, A.y + size.h - radius, color);
	drawVLine(A.x + size.w, A.y + radius, A.y + size.h - radius, color);
	gfx2dPoint_t roundPoint;
	roundPoint.x = A.x + radius;
	roundPoint.y = A.y + radius;
	roundHelper_2d(roundPoint, radius, 0, color);
	roundPoint.x = A.x + size.w - radius;
	roundPoint.y = A.y + radius;
	roundHelper_2d(roundPoint, radius, 1, color);
	roundPoint.x = A.x + size.w - radius;
	roundPoint.y = A.y + size.h - radius;
	roundHelper_2d(roundPoint, radius, 2, color);
	roundPoint.x = A.x + radius;
	roundPoint.y = A.y + size.h - radius;
	roundHelper_2d(roundPoint, radius, 3, color);
}

inline void Gfx::fillRoundHelper_2d(gfx2dPoint_t A, uint32_t radius, uint32_t side, uint16_t color) {
	int32_t x = 0, y = radius;
	int32_t e = 0, e1, e2;
	while (x <= y) {
		if ((side == 2) || (side == 3))
			drawHLine(-y + A.x, y + A.x, x + A.y, color);
		if ((side == 0) || (side == 1))
			drawHLine(-y + A.x, y + A.x, -x + A.y, color);
		e1 = e + (x << 1) + 1;
		e2 = e1 - (y << 1) + 1;
		if (e1 + e2 >= 0) {
			if ((side == 2) || (side == 3))
				drawHLine(-x + A.x, x + A.x, y + A.y, color);
			if ((side == 0) || (side == 1))
				drawHLine(-x + A.x, x + A.x, -y + A.y, color);
			y--;
			e = e2;
		} else
			e = e1;
		x++;
	}
}

void Gfx::fillRoundRect_2d(gfx2dPoint_t A, gfx2dSize_t size, uint32_t radius, uint16_t color) {
	gfx2dSize_t rect1;
	gfx2dPoint_t A1;
	rect1.w = size.w - (radius << 1);
	rect1.h = size.h;
	A1.x = A.x + radius;
	A1.y = A.y;
	fillRect_2d(A1, rect1, color);

	gfx2dSize_t rect23;
	gfx2dPoint_t A23;
	rect23.w = radius;
	rect23.h = size.h - (radius << 1);
	A23.x = A.x;
	A23.y = A.y + radius;
	fillRect_2d(A23, rect23, color);
	A23.x = A.x + size.w - radius;
	A23.y = A.y + radius;
	fillRect_2d(A23, rect23, color);

	gfx2dPoint_t roundPoint;
	roundPoint.x = A.x + radius;
	roundPoint.y = A.y + radius;
	fillRoundHelper_2d(roundPoint, radius, 0, color);
	roundPoint.x = A.x + size.w - radius;
	roundPoint.y = A.y + radius;
	fillRoundHelper_2d(roundPoint, radius, 1, color);
	roundPoint.x = A.x + size.w - radius;
	roundPoint.y = A.y + size.h - radius - 1;
	fillRoundHelper_2d(roundPoint, radius, 2, color);
	roundPoint.x = A.x + radius;
	roundPoint.y = A.y + size.h - radius - 1;
	fillRoundHelper_2d(roundPoint, radius, 3, color);
}

void Gfx::circle_2d(gfx2dPoint_t A, uint32_t radius, uint16_t color) {
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

void Gfx::fillCircle_2d(gfx2dPoint_t A, uint32_t radius, uint16_t color) {
	int32_t x = 0, y = radius;
	int32_t e = 0, e1, e2;
	while (x <= y) {
		drawHLine(-y + A.x, y + A.x, x + A.y, color);
		drawHLine(-y + A.x, y + A.x, -x + A.y, color);
		e1 = e + (x << 1) + 1;
		e2 = e1 - (y << 1) + 1;
		if (e1 + e2 >= 0) {
			drawHLine(-x + A.x, x + A.x, y + A.y, color);
			drawHLine(-x + A.x, x + A.x, -y + A.y, color);
			y--;
			e = e2;
		} else
			e = e1;
		x++;
	}
}

void Gfx::ellipse_2d(gfx2dPoint_t A, gfx2dRadius_t R, uint16_t color) {
	int32_t x = 0, y = R.ry;
	int32_t e = 0, e1, e2;
	int32_t rx2 = R.rx * R.rx;
	int32_t ry2 = R.ry * R.ry;
	int32_t fx = 0;
	int32_t fy = rx2 * R.ry;

	while (fx <= fy) {
		drawPixel(A.x + x, A.y + y, color);
		drawPixel(A.x + x, A.y - y, color);
		drawPixel(A.x - x, A.y + y, color);
		drawPixel(A.x - x, A.y - y, color);
		e1 = e + (fx << 1) + ry2;
		e2 = e1 - (fy << 1) + rx2;
		x++;
		fx += ry2;
		if ((e1 + e2) >= 0) {
			e = e2;
			y--;
			fy -= rx2;
		} else
			e = e1;
	}

	while (y >= 0) {
		drawPixel(A.x + x, A.y + y, color);
		drawPixel(A.x + x, A.y - y, color);
		drawPixel(A.x - x, A.y + y, color);
		drawPixel(A.x - x, A.y - y, color);
		e1 = e - (fy << 1) + rx2;
		e2 = e1 + (fx << 1) + ry2;
		y--;
		fy -= rx2;
		if ((e1 + e2) < 0) {
			e = e2;
			x++;
			fx += ry2;
		} else
			e = e1;
	}

}

void Gfx::fillEllipse_2d(gfx2dPoint_t A, gfx2dRadius_t R, uint16_t color) {

	int32_t x = 0, y = R.ry;
	int32_t e = 0, e1, e2;
	int32_t rx2 = R.rx * R.rx;
	int32_t ry2 = R.ry * R.ry;
	int32_t fx = 0;
	int32_t fy = rx2 * R.ry;

	while (fx <= fy) {
		e1 = e + (fx << 1) + ry2;
		e2 = e1 - (fy << 1) + rx2;
		if ((e1 + e2) >= 0) {
			drawHLine(-x + A.x, x + A.x, y + A.y, color);
			drawHLine(-x + A.x, x + A.x, -y + A.y, color);
			e = e2;
			y--;
			fy -= rx2;
		} else
			e = e1;
		x++;
		fx += ry2;
	}

	while (y >= 0) {
		drawHLine(-x + A.x, x + A.x, y + A.y, color);
		drawHLine(-x + A.x, x + A.x, -y + A.y, color);
		e1 = e - (fy << 1) + rx2;
		e2 = e1 + (fx << 1) + ry2;
		y--;
		fy -= rx2;
		if (e1 + e2 < 0) {
			e = e2;
			x++;
			fx += ry2;
		} else
			e = e1;
	}
}


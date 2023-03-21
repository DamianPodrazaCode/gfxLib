#include "gfx.h"
#include <math.h>

void gfx2d_line(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint16_t color) {

	// Algorytmy rasteryzacji lini, algorytm Bresenhama
	// https://gakko.pjwstk.edu.pl/materialy/1927/lec/wyklad-4.html#odcinki
	//554

	if (ABS(y1 - y0) > ABS(x1 - x0)) {
		// rysowanie po osi Y
		if (y0 > y1) { // ustawienie rysowania zawsze od góry do dołu
			SWAP(x0, x1);
			SWAP(y0, y1);
		}
		int dx = x1 - x0; // długość w osi X
		int dy = y1 - y0; // długość w osi Y
		register int xx = dx > 0 ? 1 : -1;  //ustalenie rysowania - prawo, lewo
		dx = ABS(dx);
		register int a = dx + dx; // zmienna pomocnicza a
		register int b = a - (dy + dy); // zmienna pomocnicza b
		register int pd = a - dy; // parametr decyzyjny
		register int x = x0; // przepisanie z ramu do rejestru, szybsze działanie pętli rysującej
		register int y = y0;
		if (xx > 0) { // rysowanie w prawo
			do {
				drawPixel(x, y, color);
				if (pd < 0) {
					y++;
					pd = pd + a;
				} else {
					y++;
					x++;
					pd = pd + b;
				}
			} while (y <= y1);
		} else { // rysowanie w lewo
			do {
				drawPixel(x, y, color);
				if (pd < 0) {
					y++;
					pd = pd + a;
				} else {
					y++;
					x--;
					pd = pd + b;
				}
			} while (y <= y1);
		}
	} else {
		// rysowanie po osi X
		if (x0 > x1) { // ustawienie rysowania zawsze od lewej do prawej
			SWAP(x0, x1);
			SWAP(y0, y1);
		}
		int dx = x1 - x0; // długość w osi X
		int dy = y1 - y0; // długość w osi Y
		register int yy = dy > 0 ? 1 : -1;  //ustalenie rysowania - góra, dół
		dy = ABS(dy);
		register int a = dy + dy; // zmienna pomocnicza a
		register int b = a - (dx + dx); // zmienna pomocnicza b
		register int pd = a - dx; // parametr decyzyjny
		register int x = x0; // przepisanie z ramu do rejestru, szybsze działanie pętli rysującej
		register int y = y0;
		if (yy > 0) { // rysowanie w górę
		do {
			drawPixel(x, y, color);
			if (pd < 0) {
				x++;
				pd = pd + a;
			} else {
				x++;
				y++;
				pd = pd + b;
			}
		} while (x <= x1);
		} else {  // rysowanie w dół
			do {
				drawPixel(x, y, color);
				if (pd < 0) {
					x++;
					pd = pd + a;
				} else {
					x++;
					y--;
					pd = pd + b;
				}
			} while (x <= x1);
		}
	}

// 554
//// zmienne pomocnicze
//	int dx, dy;
//	register int d, ai, bi, xi, yi;
//	register int x = x0, y = y0;
//	// ustalenie kierunku rysowania
//	if (x0 < x1) {
//		xi = 1;
//		dx = x1 - x0;
//	} else {
//		xi = -1;
//		dx = x0 - x1;
//	}
//	// ustalenie kierunku rysowania
//	if (y0 < y1) {
//		yi = 1;
//		dy = y1 - y0;
//	} else {
//		yi = -1;
//		dy = y0 - y1;
//	}
//	// pierwszy piksel
//	drawPixel(x, y, color);
//	// oś wiodąca OX
//	if (dx > dy) {
//		ai = (dy - dx) * 2;
//		bi = dy * 2;
//		d = bi - dx;
//		// pętla po kolejnych x
//		while (x != x1) {
//			// test współczynnika
//			if (d >= 0) {
//				x += xi;
//				y += yi;
//				d += ai;
//			} else {
//				d += bi;
//				x += xi;
//			}
//			drawPixel(x, y, color);
//		}
//	}
//	// oś wiodąca OY
//	else {
//		ai = (dx - dy) * 2;
//		bi = dx * 2;
//		d = bi - dy;
//		// pętla po kolejnych y
//		while (y != y1) {
//			// test współczynnika
//			if (d >= 0) {
//				x += xi;
//				y += yi;
//				d += ai;
//			} else {
//				d += bi;
//				y += yi;
//			}
//			drawPixel(x, y, color);
//		}
//	}

//555
//	int32_t steep = ABS(y1 - y0) > ABS(x1 - x0);
//	if (steep > 0) {
//		SWAP(x0, y0);
//		SWAP(x1, y1);
//	}
//
//	// zamiana rysowania w x, zawsze rysujemy od lewej do prawej
//	if (x0 > x1) {
//		SWAP(x0, x1);
//		SWAP(y0, y1);
//	}
//
//	register int32_t dx = x1 - x0;  // długość w osi x, abs niepotrzebny bo wcześnie zrobiona zamiana
//	register int32_t dy = ABS(y1 - y0); // długość w osi y
//	register int32_t err = dx / 2;
//	register int32_t ystep = (y0 < y1) ? 1 : -1;
//	register int x = x0, y = y0;
//
//	if (steep) {
//		for (; x <= x1; x++) {
//			drawPixel(y, x, color);
//			err -= dy;
//			if (err < 0) {
//				y += ystep;
//				err += dx;
//			}
//		}
//	} else {
//		for (; x <= x1; x++) {
//			drawPixel(x, y, color);
//			err -= dy;
//			if (err < 0) {
//				y += ystep;
//				err += dx;
//			}
//		}
//	}

//609
//	int32_t xinc1 = 0, xinc2 = 0, yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0;
//	int32_t deltax = ABS(x1 - x0);
//	int32_t deltay = ABS(y1 - y0);
//
//	xinc2 = xinc1 = (x1 >= x0) ? 1 : -1;
//	yinc2 = yinc1 = (y1 >= y0) ? 1 : -1;
//
//	if (deltax >= deltay) {
//		yinc2 = xinc1 = 0;
//		numpixels = den = deltax;
//		num = deltax << 1;
//		numadd = deltay;
//	} else {
//		yinc1 = xinc2 = 0;
//		numpixels = den = deltay;
//		num = deltay << 1;
//		numadd = deltax;
//	}
//
//	for (int32_t curpixel = 0; curpixel <= numpixels; curpixel++) {
//		drawPixel(x0, y0, color);
//		num += numadd;
//		if (num >= den) {
//			num -= den;
//			x0 += xinc1;
//			y0 += yinc1;
//		}
//		x0 += xinc2;
//		y0 += yinc2;
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
void gfx2d_fillTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint16_t color) {

	int16_t t1x, t2x, y, minx, maxx, t1xp, t2xp;
	uint8_t changed1 = 0;
	uint8_t changed2 = 0;
	int16_t signx1, signx2, dx1, dy1, dx2, dy2;
	uint32_t e1, e2;
	uint32_t i, j;

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

	t1x = t2x = x0;
	y = y0;

	dx1 = x1 - x0;
	if (dx1 < 0) {
		dx1 = -dx1;
		signx1 = -1;
	} else
		signx1 = 1;
	dy1 = y1 - y0;

	dx2 = x2 - x0;
	if (dx2 < 0) {
		dx2 = -dx2;
		signx2 = -1;
	} else
		signx2 = 1;
	dy2 = y2 - y0;

	if (dy1 > dx1) {
		SWAP(dx1, dy1);
		changed1 = 0x01;
	}
	if (dy2 > dx2) {
		SWAP(dy2, dx2);
		changed2 = 0x01;
	}

	e2 = dx2 >> 1;

	if (y0 == y1)
		goto next;
	e1 = dx1 >> 1;

	for (i = 0; i < dx1;) {
		t1xp = 0;
		t2xp = 0;
		if (t1x < t2x) {
			minx = t1x;
			maxx = t2x;
		} else {
			minx = t2x;
			maxx = t1x;
		}

		while (i < dx1) {
			i++;
			e1 += dy1;
			while (e1 >= dx1) {
				e1 -= dx1;
				if (changed1)
					t1xp = signx1;
				else
					goto next1;
			}
			if (changed1)
				break;
			else
				t1x += signx1;
		}
		next1: while (1) {
			e2 += dy2;
			while (e2 >= dx2) {
				e2 -= dx2;
				if (changed2)
					t2xp = signx2;
				else
					goto next2;
			}
			if (changed2)
				break;
			else
				t2x += signx2;
		}
		next2: if (minx > t1x)
			minx = t1x;
		if (minx > t2x)
			minx = t2x;
		if (maxx < t1x)
			maxx = t1x;
		if (maxx < t2x)
			maxx = t2x;
		drawHLine(minx, maxx, y, color);
		if (!changed1)
			t1x += signx1;
		t1x += t1xp;
		if (!changed2)
			t2x += signx2;
		t2x += t2xp;
		y += 1;
		if (y == y1)
			break;

	}
	next: dx1 = x2 - x1;
	if (dx1 < 0) {
		dx1 = -dx1;
		signx1 = -1;
	} else
		signx1 = 1;
	dy1 = y2 - y1;
	t1x = x1;

	if (dy1 > dx1) {
		SWAP(dy1, dx1);
		changed1 = 0x01;
	} else
		changed1 = 0x00;

	e1 = dx1 >> 1;

	for (j = 0; j <= dx1; j++) {
		t1xp = 0;
		t2xp = 0;
		if (t1x < t2x) {
			minx = t1x;
			maxx = t2x;
		} else {
			minx = t2x;
			maxx = t1x;
		}
		while (j < dx1) {
			e1 += dy1;
			while (e1 >= dx1) {
				e1 -= dx1;
				if (changed1) {
					t1xp = signx1;
					break;
				} else
					goto next3;
			}
			if (changed1)
				break;
			else
				t1x += signx1;
			if (j < dx1)
				j++;
		}
		next3: while (t2x != x2) {
			e2 += dy2;
			while (e2 >= dx2) {
				e2 -= dx2;
				if (changed2)
					t2xp = signx2;
				else
					goto next4;
			}
			if (changed2)
				break;
			else
				t2x += signx2;
		}
		next4:

		if (minx > t1x)
			minx = t1x;
		if (minx > t2x)
			minx = t2x;
		if (maxx < t1x)
			maxx = t1x;
		if (maxx < t2x)
			maxx = t2x;
		drawHLine(minx, maxx, y, color);
		if (!changed1)
			t1x += signx1;
		t1x += t1xp;
		if (!changed2)
			t2x += signx2;
		t2x += t2xp;
		y += 1;
		if (y > y2)
			return;
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

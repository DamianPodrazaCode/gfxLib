#include "gfx.h"

void gfx2d_line(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint16_t color) {

	int32_t steep = ABS(y1 - y0) > ABS(x1 - x0);
	if (steep > 0) {
		SWAP(x0, y0);
		SWAP(x1, y1);
	}

	if (x0 > x1) {
		SWAP(x0, x1);
		SWAP(y0, y1);
	}

	int32_t dx = x1 - x0;
	int32_t dy = ABS(y1 - y0);
	int32_t err = dx / 2;
	int32_t ystep = (y0 < y1) ? 1 : -1;

	if (steep) {
		for (; x0 <= x1; x0++) {
			drawPixel(y0, x0, color);
			err -= dy;
			if (err < 0) {
				y0 += ystep;
				err += dx;
			}
		}
	} else {
		for (; x0 <= x1; x0++) {
			drawPixel(x0, y0, color);
			err -= dy;
			if (err < 0) {
				y0 += ystep;
				err += dx;
			}
		}
	}

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

void gfx2d_circle(int32_t x, int32_t y, uint32_t r, uint16_t color) {
}

void gfx2d_fillCircle(int32_t x, int32_t y, uint32_t r, uint16_t color) {
}

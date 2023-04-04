#include "drvSSD1963.h"

ScrDrv::ScrDrv() {
}

inline void ScrDrv::lcdSetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
	writeCMD(ILI9341_CASET);
	writeDATA(x0 >> 8);
	writeDATA(x0);
	writeDATA(x1 >> 8);
	writeDATA(x1);
	writeCMD(ILI9341_PASET);
	writeDATA(y0 >> 8);
	writeDATA(y0);
	writeDATA(y1 >> 8);
	writeDATA(y1);
	writeCMD(ILI9341_RAMWR);
}

inline void ScrDrv::lcdSetOrient(scrOrient_t orientation) {
	// ILI9341_MADCTL
	// bity D7	D6	D5	D4	D3	D2	D1	D0
	//		MY	MX	MV	ML	BGR	MH	0	0
	switch (orientation) {
	case scrOrientPortrait_0:
		width = ILI9341_shorter_side_pixels;
		height = ILI9341_longer_side_pixels;
		writeCMD(ILI9341_MADCTL);
		writeDATA(0b01001000);
		break;
	case scrOrientLandscape_90:
		width = ILI9341_longer_side_pixels;
		height = ILI9341_shorter_side_pixels;
		writeCMD(ILI9341_MADCTL);
		writeDATA(0b00101000);
		break;
	case scrOrientPortrait_180:
		width = ILI9341_shorter_side_pixels;
		height = ILI9341_longer_side_pixels;
		writeCMD(ILI9341_MADCTL);
		writeDATA(0b10001000);
		break;
	case scrOrientLandscape_270:
		width = ILI9341_longer_side_pixels;
		height = ILI9341_shorter_side_pixels;
		writeCMD(ILI9341_MADCTL);
		writeDATA(0b11101000);
		break;
	default: //lcdOrientPortrait_0
		width = ILI9341_shorter_side_pixels;
		height = ILI9341_longer_side_pixels;
		writeCMD(ILI9341_MADCTL);
		writeDATA(0b01001000);
		break;
	}
	lcdSetWindow(0, 0, width - 1, height - 1);
}

void ScrDrv::drvInit(scrOrient_t orientation) {
	lcdBlOff(); // wyłączenie podświetlenia
	lcdDelayMs(1); // HW reset
	lcdRstLOW();
	lcdDelayMs(1);
	lcdRstHI();
	lcdDelayMs(120);
	lcdSetOrient(orientation); // ustawienie orientacji i trybu BGR na wyświetlaczu
	writeCMD(ILI9341_PIXSET); // ustawienie piksela na 16Bit
	writeDATA(0x55);
	writeCMD(ILI9341_SLPOUT); // wyjście z trybu uśpienia
	lcdDelayMs(120);
	writeCMD(ILI9341_DISPON); // włączenie wyświetlania
	clearScr(COLOR_BLACK);
	lcdBlOn(); // właczenie podświetlenia
}

void ScrDrv::clearScr(uint16_t color) {
	lcdSetWindow(0, 0, width - 1, height - 1);
	int dimensions = width * height;
	while (dimensions--) {
		writeDATA(color);
	}
}

void ScrDrv::drawPixel(int32_t x, int32_t y, uint16_t color) {
	if ((x < width) && (y < height) && (x >= 0) && (y >= 0)) {
		lcdSetWindow(x, y, x, y);
		writeDATA(color);
	}
}

void ScrDrv::drawHLine(int32_t x1, int32_t x2, int32_t y, uint16_t color) {
	if ((x1 > width - 1) && (x2 > width - 1)) //jeżeli linia po za ekranem z prawej strony to nie rysuj w ogóle
		return;
	if ((x1 < 0) && (x2 < 0)) //jeżeli linia po za ekranem z lewej strony to nie rysuj w ogóle
		return;
	if (x1 > x2) // sortowanie stron
		SWAP(x1, x2);
	if (x2 > width - 1)
		x2 = width - 1;
	if (x1 < 0)
		x1 = 0;
	if ((y < height) && (y >= 0)) {
		lcdSetWindow(x1, y, x2, y);
		for (int16_t i = x1; i < x2; i++)
			writeDATA(color);
	}
}

void ScrDrv::drawVLine(int32_t x, int32_t y1, int32_t y2, uint16_t color) {
	if ((y1 > height - 1) && (y2 > height - 1)) //jeżeli linia po za ekranem z dolnej strony to nie rysuj w ogóle
		return;
	if ((y1 < 0) && (y2 < 0)) //jeżeli linia po za ekranem z górnej strony to nie rysuj w ogóle
		return;
	if (y1 > y2)
		SWAP(y1, y2);
	if (y2 > height - 1)
		y2 = height - 1;
	if (y1 < 0)
		y1 = 0;
	lcdSetWindow(x, y1, x, y2);
	for (int16_t i = y1; i < y2; i++)
		writeDATA(color);
}

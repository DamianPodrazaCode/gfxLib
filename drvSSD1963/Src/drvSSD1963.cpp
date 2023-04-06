#include "drvSSD1963.h"

ScrDrv::ScrDrv() {
}

inline void ScrDrv::lcdSetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {

//		writeCMD(SSD1963_set_column_address);
//		writeDATA(0);
//		writeDATA(0);
//		writeDATA(HDP >> 8);
//		writeDATA(HDP & 0x00ff);
//		writeCMD(SSD1963_set_page_address);
//		writeDATA(0);
//		writeDATA(0);
//		writeDATA(VDP >> 8);
//		writeDATA(VDP & 0x00ff);
//		writeCMD(SSD1963_write_memory_start);
//		//writeCMD(0x002c);
//		for (int count = 0; count < 130560; count++) {
//			writeDATA(COLOR_RED);
//		}

	writeCMD(SSD1963_set_column_address);
	writeDATA(x0 >> 8);
	writeDATA(x0);
	writeDATA(x1 >> 8);
	writeDATA(x1);
	writeCMD(SSD1963_set_page_address);
	writeDATA(y0 >> 8);
	writeDATA(y0);
	writeDATA(y1 >> 8);
	writeDATA(y1);
	writeCMD(SSD1963_write_memory_start);
}

inline void ScrDrv::lcdSetOrient(scrOrient_t orientation) {
	switch (orientation) {
	case scrOrientPortrait_0:
		width = SSD1963_shorter_side_pixels;
		height = SSD1963_longer_side_pixels;
//		writeCMD(SSD1963_set_address_mode);
//		writeDATA(0b00001000);
		break;
	case scrOrientLandscape_90:
		width = SSD1963_longer_side_pixels;
		height = SSD1963_shorter_side_pixels;
//		writeCMD(SSD1963_set_address_mode);
//		writeDATA(0b00101000);
		break;
	case scrOrientPortrait_180:
		width = SSD1963_shorter_side_pixels;
		height = SSD1963_longer_side_pixels;
//		writeCMD(SSD1963_set_address_mode);
//		writeDATA(0b10001000);
		break;
	case scrOrientLandscape_270:
		width = SSD1963_longer_side_pixels;
		height = SSD1963_shorter_side_pixels;
//		writeCMD(SSD1963_set_address_mode);
//		writeDATA(0b11101000);
		break;
	default: //lcdOrientPortrait_0
		width = SSD1963_shorter_side_pixels;
		height = SSD1963_longer_side_pixels;
//		writeCMD(SSD1963_set_address_mode);
//		writeDATA(0b01001000);
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
	// -----------------------------------------

	writeCMD(SSD1963_set_pll_mn);
	writeDATA(0x0023);
	writeDATA(0x0002);
	writeDATA(0x0004);
	writeCMD(SSD1963_set_pll);
	writeDATA(0x0001);
	lcdDelayMs(1);
	writeCMD(SSD1963_set_pll);
	writeDATA(0x0003);
	lcdDelayMs(5);

	writeCMD(SSD1963_soft_reset);
	lcdDelayMs(5);

	writeCMD(SSD1963_set_lshift_freq);
	writeDATA(0x0001);
	writeDATA(0x0033);
	writeDATA(0x0032);

	writeCMD(SSD1963_set_lcd_mode);
	writeDATA(0x0020);
	writeDATA(0x0000);
	writeDATA((HDP >> 8) & 0X00FF);
	writeDATA(HDP & 0X00FF);
	writeDATA((VDP >> 8) & 0X00FF);
	writeDATA(VDP & 0X00FF);
	writeDATA(0x0000);

	writeCMD(SSD1963_set_hori_period);
	writeDATA((HT >> 8) & 0X00FF);
	writeDATA(HT & 0X00FF);
	writeDATA((HPS >> 8) & 0X00FF);
	writeDATA(HPS & 0X00FF);
	writeDATA(HPW);
	writeDATA((LPS >> 8) & 0X00FF);
	writeDATA(LPS & 0X00FF);
	writeDATA(0x0000);

	writeCMD(SSD1963_set_vert_period);
	writeDATA((VT >> 8) & 0X00FF);   //Set VT
	writeDATA(VT & 0X00FF);
	writeDATA((VPS >> 8) & 0X00FF);
	writeDATA(VPS & 0X00FF);
	writeDATA(VPW);
	writeDATA((FPS >> 8) & 0X00FF);
	writeDATA(FPS & 0X00FF);

	writeCMD(SSD1963_set_pixel_data_interface);
	writeDATA(0x0003);

	writeCMD(SSD1963_enter_invert_mode);

	writeCMD(SSD1963_set_post_proc);
	writeDATA(0x0080);
	writeDATA(0x0080);
	writeDATA(0x0080);
	writeDATA(0x0001);

	lcdSetOrient(orientation); // ustawienie orientacji i trybu BGR na wyświetlaczu

	writeCMD(SSD1963_set_address_mode);
	writeDATA(0b00001010);

	writeCMD(SSD1963_set_display_on);
	// -----------------------------------------

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

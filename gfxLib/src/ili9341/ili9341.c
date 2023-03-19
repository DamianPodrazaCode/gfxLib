/*
 * ili9341.c
 *
 *  Created on: Dec 31, 2022
 *      Author: ZoMbiE
 */
#include "../ili9341/ili9341.h"

#include "main.h"

#include "../ili9341/hardwareMCU.h"
#include "../ili9341/registers.h"

#define ILI9341_shorter_side_pixels	240
#define ILI9341_longer_side_pixels 	320
#define swap(a, b) { int16_t t = a; a = b; b = t; }

lcdPropertiesTypeDef lcdProp = { 0, 0, 0 };


static inline void lcdSetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
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

void lcdSetOrient(lcdOrient orientation) {
	// ILI9341_MADCTL
	// bity D7	D6	D5	D4	D3	D2	D1	D0
	//		MY	MX	MV	ML	BGR	MH	0	0
	switch (orientation) {
	case lcdOrientPortrait_0:
		lcdProp.width = ILI9341_shorter_side_pixels;
		lcdProp.height = ILI9341_longer_side_pixels;
		writeCMD(ILI9341_MADCTL);
		writeDATA(0b01001000);
		break;
	case lcdOrientLandscape_90:
		lcdProp.width = ILI9341_longer_side_pixels;
		lcdProp.height = ILI9341_shorter_side_pixels;
		writeCMD(ILI9341_MADCTL);
		writeDATA(0b00101000);
		break;
	case lcdOrientPortrait_180:
		lcdProp.width = ILI9341_shorter_side_pixels;
		lcdProp.height = ILI9341_longer_side_pixels;
		writeCMD(ILI9341_MADCTL);
		writeDATA(0b10001000);
		break;
	case lcdOrientLandscape_270:
		lcdProp.width = ILI9341_longer_side_pixels;
		lcdProp.height = ILI9341_shorter_side_pixels;
		writeCMD(ILI9341_MADCTL);
		writeDATA(0b11101000);
		break;
	default: //lcdOrientPortrait_0
		lcdProp.width = ILI9341_shorter_side_pixels;
		lcdProp.height = ILI9341_longer_side_pixels;
		writeCMD(ILI9341_MADCTL);
		writeDATA(0b01001000);
		break;
	}
	lcdSetWindow(0, 0, lcdProp.width - 1, lcdProp.height - 1);
}

void lcdInit(lcdOrient orientation) {
	initExtraHardware();
	lcdBlOff(); // wyłączenie podświetlenia
	HAL_Delay(1); // HW reset
	lcdRstLOW();
	HAL_Delay(1);
	lcdRstHI();
	HAL_Delay(120);
	lcdSetOrient(orientation); // ustawienie orientacji i trybu BGR na wyświetlaczu
	writeCMD(ILI9341_PIXSET); // ustawienie piksela na 16Bit
	writeDATA(0x55);
	writeCMD(ILI9341_SLPOUT); // wyjście z trybu uśpienia
	HAL_Delay(120);
	writeCMD(ILI9341_DISPON); // włączenie wyświetlania
	lcdBlOn(); // właczenie podświetlenia
}

void lcdClear(uint16_t color) {
	lcdSetWindow(0, 0, lcdProp.width - 1, lcdProp.height - 1);
	int dimensions = lcdProp.width * lcdProp.height;
	while (dimensions--) {
		writeDATA(color);
	}
}

void lcdDrawPixel(uint16_t x, uint16_t y, uint16_t color) {
	lcdSetWindow(x, y, x, y);
	writeDATA(color);
}

void lcdHLine(int16_t x1, int16_t x2, int16_t y, uint16_t color) {
	lcdSetWindow(x1, y, x2, y);
	if (x1 > x2)
		swap(x1, x2);
	for (uint16_t i = x1; i < x2; i++)
		writeDATA(color);
}

void lcdVLine(int16_t x, int16_t y1, int16_t y2, uint16_t color) {
	lcdSetWindow(x, y1, x, y2);
	if (y1 > y2)
		swap(y1, y2);
	for (uint16_t i = y1; i < y2; i++)
		writeDATA(color);
}

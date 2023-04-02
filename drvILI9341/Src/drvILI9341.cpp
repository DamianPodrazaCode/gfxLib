#include "drvILI9341.h"

DrvILI9341::DrvILI9341() {
}

inline void DrvILI9341::lcdSetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
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

inline void DrvILI9341::lcdSetOrient(lcdOrient_t orientation) {
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

void DrvILI9341::drv_init(lcdOrient_t orientation) {
	initExtraHardware();
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
	lcdBlOn(); // właczenie podświetlenia
}

void DrvILI9341::clearScr(uint16_t color) {
	lcdSetWindow(0, 0, lcdProp.width - 1, lcdProp.height - 1);
	int dimensions = lcdProp.width * lcdProp.height;
	while (dimensions--) {
		writeDATA(color);
	}
}

inline void DrvILI9341::drawPixel(int32_t x, int32_t y, uint16_t color) {
	if ((x < lcdProp.width) && (y < lcdProp.height) && (x >= 0) && (y >= 0)) {
		lcdSetWindow(x, y, x, y);
		writeDATA(color);
	}
}

inline void DrvILI9341::drawHLine(int32_t x1, int32_t x2, int32_t y, uint16_t color) {
	if ((x1 > lcdProp.width - 1) && (x2 > lcdProp.width - 1)) //jeżeli linia po za ekranem z prawej strony to nie rysuj w ogóle
		return;
	if ((x1 < 0) && (x2 < 0)) //jeżeli linia po za ekranem z lewej strony to nie rysuj w ogóle
		return;
	if (x1 > x2) // sortowanie stron
		swap(x1, x2);
	if (x2 > lcdProp.width - 1)
		x2 = lcdProp.width - 1;
	if (x1 < 0)
		x1 = 0;
	if ((y < lcdProp.height) && (y >= 0)) {
		lcdSetWindow(x1, y, x2, y);
		for (int16_t i = x1; i < x2; i++)
			writeDATA(color);
	}
}

inline void DrvILI9341::drawVLine(int32_t x, int32_t y1, int32_t y2, uint16_t color) {
	if ((y1 > lcdProp.height - 1) && (y2 > lcdProp.height - 1)) //jeżeli linia po za ekranem z dolnej strony to nie rysuj w ogóle
		return;
	if ((y1 < 0) && (y2 < 0)) //jeżeli linia po za ekranem z górnej strony to nie rysuj w ogóle
		return;
	if (y1 > y2)
		swap(y1, y2);
	if (y2 > lcdProp.height - 1)
		y2 = lcdProp.height - 1;
	if (y1 < 0)
		y1 = 0;
	lcdSetWindow(x, y1, x, y2);
	for (int16_t i = y1; i < y2; i++)
		writeDATA(color);
}

//inline void copyBuffer(uint16_t *buffer, int32_t x, int32_t y, uint32_t heigh, uint32_t width) {
//}

//// funkcje __weak, które trzeba stworzyć, zależnie od platformy
//
//__weak void initExtraHardware() {
//	// funkcja inicjalizyjąca dodatkowe ustawienia sprzętowe np.DMA
//}
//__weak void writeCMD(uint16_t cmd) {
//	// komenda do LCD
//}
//__weak void writeDATA(uint16_t data) {
//	// dane do LCD
//}
//__weak bool writeBUFFER(uint32_t buffer, uint32_t size) {
//	// kopiowanie całego bloku danych do LCD
//	return false;
//}
//__weak void lcdBlOn() {
//	// włączenie podświetlenia LCD
//}
//__weak void lcdBlOff() {
//	// wyłączenie podświetlenia LCD
//}
//__weak void lcdRstHI() {
//	// reset stan wysoki
//}
//__weak void lcdRstLOW() {
//	// reset stan niski
//}
//__weak void lcdDelayMs(uint32_t ms) {
//	// delay w ms
//}

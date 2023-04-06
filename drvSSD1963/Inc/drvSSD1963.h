#ifndef SSD1963_H_
#define SSD1963_H_

#include "hwPort.h"
#include "colors.h"
#include "registers.h"
#include "common.h"
#include <stdint.h>
#include <stdbool.h>

class ScrDrv: HwPort {
public:
	ScrDrv();

private:
	const uint16_t HDP = 479; //width

	const uint16_t HT = 531;
	const uint16_t HPS = 43;
	const uint16_t LPS = 8;
	const uint16_t HPW = 10;

	const uint16_t VDP = 271; //height
	const uint16_t VT = 288;
	const uint16_t VPS = 12;
	const uint16_t FPS = 4;
	const uint16_t VPW = 10;

protected:
	int32_t width;
	int32_t height;

	inline void lcdSetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);

	void drvInit();
	void clearScr(uint16_t color);
	void drawPixel(int32_t x, int32_t y, uint16_t color);
	void drawHLine(int32_t x1, int32_t x2, int32_t y, uint16_t color);
	void drawVLine(int32_t x, int32_t y1, int32_t y2, uint16_t color);
};

#endif /* SSD1963_H_ */

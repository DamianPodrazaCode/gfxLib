#ifndef SSD1963_H_
#define SSD1963_H_

#include "hwPort.h"
#include "colors.h"
#include "registers.h"
#include "common.h"
#include <stdint.h>
#include <stdbool.h>

typedef enum {
	scrOrientPortrait_0, scrOrientLandscape_90, scrOrientPortrait_180, scrOrientLandscape_270
} scrOrient_t;

class ScrDrv: HwPort {
public:
	ScrDrv();

private:
	const uint16_t SSD1963_shorter_side_pixels = 272;
	const uint16_t SSD1963_longer_side_pixels = 480;

	const uint16_t HDP = 479;

	const uint16_t HT = 531;
	const uint16_t HPS = 43;
	const uint16_t LPS = 8;
	const uint16_t HPW = 10;

	const uint16_t VDP = 271;
	const uint16_t VT = 288;
	const uint16_t VPS = 12;
	const uint16_t FPS = 4;
	const uint16_t VPW = 10;

protected:
public:
	int32_t width;
	int32_t height;
	scrOrient_t orientation;

	inline void lcdSetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
	inline void lcdSetOrient(scrOrient_t orientation);

	void drvInit(scrOrient_t orientation);
	void clearScr(uint16_t color);
	void drawPixel(int32_t x, int32_t y, uint16_t color);
	void drawHLine(int32_t x1, int32_t x2, int32_t y, uint16_t color);
	void drawVLine(int32_t x, int32_t y1, int32_t y2, uint16_t color);
};

#endif /* SSD1963_H_ */

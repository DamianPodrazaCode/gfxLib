#ifndef ILI9341_H_
#define ILI9341_H_

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
	const uint16_t ILI9341_shorter_side_pixels = 240;
	const uint16_t ILI9341_longer_side_pixels = 320;

protected:
	int32_t width;
	int32_t height;
	scrOrient_t orientation;

	inline void lcdSetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
	inline void lcdSetOrient(scrOrient_t orientation);

	void drv_init(scrOrient_t orientation);
	void clearScr(uint16_t color);
	void drawPixel(int32_t x, int32_t y, uint16_t color);
	void drawHLine(int32_t x1, int32_t x2, int32_t y, uint16_t color);
	void drawVLine(int32_t x, int32_t y1, int32_t y2, uint16_t color);
};

#endif /* ILI9341_H_ */

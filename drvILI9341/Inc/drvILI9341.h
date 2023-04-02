#ifndef ILI9341_H_
#define ILI9341_H_

#include "hwPort.h"
#include "colors.h"
#include "registers.h"
#include <stdint.h>
#include <stdbool.h>

#define ILI9341_shorter_side_pixels	240
#define ILI9341_longer_side_pixels 	320
#define swap(a, b) { int32_t t = a; a = b; b = t; }

typedef enum {
	lcdOrientPortrait_0, lcdOrientLandscape_90, lcdOrientPortrait_180, lcdOrientLandscape_270
} lcdOrient_t;

typedef struct {
	int32_t width;
	int32_t height;
	lcdOrient_t orientation;
} lcdProperties_t;

class DrvILI9341: HwPort {
public:
	DrvILI9341();
	void drv_init(lcdOrient_t orientation);
	void clearScr(uint16_t color);

private:
	lcdProperties_t lcdProp;

	inline void lcdSetWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
	inline void lcdSetOrient(lcdOrient_t orientation);

protected:

	void drawPixel(int32_t x, int32_t y, uint16_t color);
	void drawHLine(int32_t x1, int32_t x2, int32_t y, uint16_t color);
	void drawVLine(int32_t x, int32_t y1, int32_t y2, uint16_t color);
};

//extern lcdProperties_t lcdProp;

//// funkcje __weak, które trzeba stworzyć, zależnie od platformy
//__weak void initExtraHardware();
//__weak void writeCMD(uint16_t cmd);
//__weak void writeDATA(uint16_t data);
//__weak void lcdBlOn();
//__weak void lcdBlOff();
//__weak void lcdRstHI();
//__weak void lcdRstLOW();
//__weak void lcdDelayMs(uint32_t ms);

#endif /* ILI9341_H_ */

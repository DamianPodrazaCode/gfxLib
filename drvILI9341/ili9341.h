#ifndef ILI9341_H_
#define ILI9341_H_

#include "colors.h"
#include "registers.h"
#include <stdint.h>
#include <stdbool.h>

#define ILI9341_shorter_side_pixels	240
#define ILI9341_longer_side_pixels 	320
#define swap(a, b) { int32_t t = a; a = b; b = t; }

#ifndef __weak
#define __weak   __attribute__((weak))
#endif // __weak

typedef enum {
	lcdOrientPortrait_0, lcdOrientLandscape_90, lcdOrientPortrait_180, lcdOrientLandscape_270
} lcdOrient;

typedef struct {
	uint32_t width;
	uint32_t height;
	lcdOrient orientation;
} lcdPropertiesTypeDef;

extern lcdPropertiesTypeDef lcdProp;

void ili9341_init(lcdOrient orientation);

void clearScr(uint16_t color);
void drawPixel(int32_t x, int32_t y, uint16_t color);
void drawHLine(int32_t x1, int32_t x2, int32_t y, uint16_t color);
void drawVLine(int32_t x, int32_t y1, int32_t y2, uint16_t color);
void copyBuffer(uint16_t *buffer, int32_t x, int32_t y, uint32_t heigh, uint32_t width);

// funkcje __weak, które trzeba stworzyć, zależnie od platformy
__weak void initExtraHardware();
__weak void writeCMD(uint16_t cmd);
__weak void writeDATA(uint16_t data);
__weak bool writeBUFFER(uint32_t buffer, uint32_t size);
__weak void lcdBlOn();
__weak void lcdBlOff();
__weak void lcdRstHI();
__weak void lcdRstLOW();
__weak void lcdDelayMs(uint32_t ms);

#endif /* ILI9341_H_ */

/*
 * ili9341.h
 *
 *  Created on: Dec 31, 2022
 *      Author: ZoMbiE
 */

#ifndef ILI9341_H_
#define ILI9341_H_

#include "main.h"
#include "colors.h"

typedef enum {
	lcdOrientPortrait_0, lcdOrientLandscape_90, lcdOrientPortrait_180, lcdOrientLandscape_270
} lcdOrient;

typedef struct {
	uint16_t width;
	uint16_t height;
	lcdOrient orientation;
} lcdPropertiesTypeDef;

extern lcdPropertiesTypeDef lcdProp;

void lcdInit(lcdOrient orientation);
void lcdClear(uint16_t color);
void lcdDrawPixel(uint16_t x, uint16_t y, uint16_t color);
void lcdHLine(int16_t x1, int16_t x2, int16_t y, uint16_t color);
void lcdVLine(int16_t x, int16_t y1, int16_t y2, uint16_t color);

#endif /* ILI9341_H_ */

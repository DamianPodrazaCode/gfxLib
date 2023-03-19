#ifndef GFX_H
#define GFX_H

#include <stdint.h>
#include <stdbool.h>
//#include <math.h>

#define ABS(X)                 ((X) > 0 ? (X) : -(X))
#define SWAP(a, b) 			   { int32_t t = a; a = b; b = t; }

#ifndef __weak
#define __weak   __attribute__((weak))
#endif // __weak 

typedef struct {
	int width;
	int height;
} gfxPropertiesTypeDef;

extern gfxPropertiesTypeDef gfxProp;

void gfx_init(int screenX, int screenY);

// funkcje podstawowe definiowane na zewnątrz
__weak void clearScr(uint16_t color);
__weak void drawPixel(int32_t x, int32_t y, uint16_t color);
__weak void drawHLine(int32_t x1, int32_t x2, int32_t y, uint16_t color);
__weak void drawVLine(int32_t x, int32_t y1, int32_t y2, uint16_t color);
__weak void copyBuffer(uint16_t *buffer, int32_t x, int32_t y, uint32_t heigh, uint32_t width);

// rysowanie w 2d, definicje funkcji znajdują sie w gfx2d.c
void gfx2d_line(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint16_t color);
void gfx2d_circle(int32_t x, int32_t y, uint32_t r, uint16_t color);
void gfx2d_fillCircle(int32_t x, int32_t y, uint32_t r, uint16_t color);

// rysowanie w 3d, definicje funkcji znajdują sie w gfx3d.c

// rysowanie tekstu, definicje funkcji znajdują sie w gfxText.c

#endif //GFX_H

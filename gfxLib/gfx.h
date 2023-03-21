#ifndef GFX_H
#define GFX_H

#include <stdint.h>
#include <stdbool.h>
//#include <math.h>

#define ABS(X)                 ((X) > 0 ? (X) : -(X))
//#define ABS(X)                 {int a=X>>31; X=((X^a)-a);}
#define SWAP(a, b) 		{ int32_t t = a; a = b; b = t; }
//#define SWAP(a, b) 		{ a ^= b; b ^= a; a ^= b;}
//#define SWAP(a, b) 		{ a -= b; b += a; a = b - a; }
#define SGN(x)			(x > 0) ? 1 : ((x < 0) ? -1 : 0)

#ifndef __weak
#define __weak   __attribute__((weak))
#endif // __weak 

typedef struct {
	int width;
	int height;
} gfxPropertiesTypeDef;

typedef struct {
	int32_t X;
	int32_t Y;
} gfxPoint;

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
void gfx2d_triangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint16_t color);
void gfx2d_rect(int32_t x, int32_t y, int32_t width, int32_t height, uint16_t color);
void gfx2d_roundRect(int32_t x, int32_t y, int32_t width, int32_t height, uint32_t r, uint16_t color);
void gfx2d_circle(int32_t x, int32_t y, uint32_t r, uint16_t color);
void gfx2d_polygon(gfxPoint *points, uint32_t pointCount, uint16_t color);
void gfx2d_ellipse(int32_t Xpos, int32_t Ypos, uint32_t XRadius, uint32_t YRadius, uint16_t color);
void gfx2d_fillTriangle(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint16_t color);
void gfx2d_fillRect(int32_t x, int32_t y, int32_t width, int32_t height, uint16_t color);
void gfx2d_fillRoundRect(int32_t x, int32_t y, int32_t width, int32_t height, uint32_t r, uint16_t color);
void gfx2d_fillCircle(int32_t x, int32_t y, uint32_t r, uint16_t color);
void gfx2d_fillPolygon(gfxPoint *points, uint32_t pointCount, uint16_t color);
void gfx2d_fillEllipse(int32_t Xpos, int32_t Ypos, uint32_t XRadius, uint32_t YRadius, uint16_t color);

// rysowanie w 3d, definicje funkcji znajdują sie w gfx3d.c

// rysowanie tekstu, definicje funkcji znajdują sie w gfxText.c

#endif //GFX_H

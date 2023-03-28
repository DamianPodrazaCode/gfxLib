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
#define MIN(a,b) 		(((a)<(b))?(a):(b))
#define MAX(a,b) 		(((a)>(b))?(a):(b))

#ifndef __weak
#define __weak   __attribute__((weak))
#endif // __weak 

typedef struct {
	int width;
	int height;
} gfxScreenProperties_t;

typedef struct {
	int32_t x;
	int32_t y;
	uint16_t color;
} gfx2dPoint_t;

typedef struct {
	int32_t w; //szerokość
	int32_t h; //wysokość
} gfx2dSize_t;

typedef struct {
	int32_t rx; //szerokość
	int32_t ry; //wysokość
} gfx2dRadius_t;



extern gfxScreenProperties_t gfxProp;

void gfx_init(int screenX, int screenY);

// funkcje podstawowe definiowane na zewnątrz
__weak void clearScr(uint16_t color);
__weak void drawPixel(int32_t x, int32_t y, uint16_t color);
__weak void drawHLine(int32_t x1, int32_t x2, int32_t y, uint16_t color);
__weak void drawVLine(int32_t x, int32_t y1, int32_t y2, uint16_t color);
__weak void copyBuffer(uint16_t *buffer, int32_t x, int32_t y, uint32_t heigh, uint32_t width);

// rysowanie w 2d, definicje funkcji znajdują sie w gfx2d.c
void gfx2d_line(gfx2dPoint_t A, gfx2dPoint_t B, uint16_t color);

void gfx2d_triangle(gfx2dPoint_t A, gfx2dPoint_t B, gfx2dPoint_t C, uint16_t color);
void gfx2d_fillTriangle(gfx2dPoint_t A, gfx2dPoint_t B, gfx2dPoint_t C, uint16_t color);

void gfx2d_rect(gfx2dPoint_t A, gfx2dSize_t size, uint16_t color);
void gfx2d_fillRect(gfx2dPoint_t A, gfx2dSize_t size, uint16_t color);

void gfx2d_roundRect(gfx2dPoint_t A, gfx2dSize_t size, uint32_t radius, uint16_t color);
void gfx2d_fillRoundRect(gfx2dPoint_t A, gfx2dSize_t size, uint32_t radius, uint16_t color);

void gfx2d_circle(gfx2dPoint_t A, uint32_t radius, uint16_t color);
void gfx2d_fillCircle(gfx2dPoint_t A, uint32_t radius, uint16_t color);

void gfx2d_ellipse(gfx2dPoint_t A, gfx2dRadius_t R, uint16_t color);
void gfx2d_fillEllipse(gfx2dPoint_t A, gfx2dRadius_t R, uint16_t color);

void gfx2d_polygon(gfx2dPoint_t *pPoint, uint32_t pointCount, uint16_t color);
void gfx2d_fillPolygon(gfx2dPoint_t *pPoint, uint32_t pointCount, uint16_t color);

// rysowanie w 3d, definicje funkcji znajdują sie w gfx3d.c

// rysowanie tekstu, definicje funkcji znajdują sie w gfxText.c

#endif //GFX_H

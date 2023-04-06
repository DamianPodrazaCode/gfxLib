#ifndef GFX_H
#define GFX_H

#include "common.h"
#include <stdint.h>
#include <stdbool.h>

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

class Gfx: ScrDrv {
public:
	Gfx();

	int32_t scrWidth;
	int32_t scrHeight;

	//void init(scrOrient_t scrOrient, int screenX = 0, int screenY = 0);
	void init(int screenX = 0, int screenY = 0);
	void clr(uint16_t color);

	void line_2d(gfx2dPoint_t A, gfx2dPoint_t B, uint16_t color);
	void triangle_2d(gfx2dPoint_t A, gfx2dPoint_t B, gfx2dPoint_t C, uint16_t color);
	void fillTriangle_2d(gfx2dPoint_t A, gfx2dPoint_t B, gfx2dPoint_t C, uint16_t color);
	void rect_2d(gfx2dPoint_t A, gfx2dSize_t size, uint16_t color);
	void fillRect_2d(gfx2dPoint_t A, gfx2dSize_t size, uint16_t color);
	void roundRect_2d(gfx2dPoint_t A, gfx2dSize_t size, uint32_t radius, uint16_t color);
	void fillRoundRect_2d(gfx2dPoint_t A, gfx2dSize_t size, uint32_t radius, uint16_t color);
	void circle_2d(gfx2dPoint_t A, uint32_t radius, uint16_t color);
	void fillCircle_2d(gfx2dPoint_t A, uint32_t radius, uint16_t color);
	void ellipse_2d(gfx2dPoint_t A, gfx2dRadius_t R, uint16_t color);
	void fillEllipse_2d(gfx2dPoint_t A, gfx2dRadius_t R, uint16_t color);

private:

	typedef struct {
		int32_t e;
		int32_t kx;
		int32_t ky;
		int32_t dx;
		int32_t dy;
		int32_t x;
		int32_t y;
	} line2dComplex_t;

	inline void lineInit_2d(line2dComplex_t *pline, gfx2dPoint_t *pA, gfx2dPoint_t *pB);
	inline void lineStep_2d(line2dComplex_t *pline);
	inline void roundHelper_2d(gfx2dPoint_t A, uint32_t radius, uint32_t side, uint16_t color);
	inline void fillRoundHelper_2d(gfx2dPoint_t A, uint32_t radius, uint32_t side, uint16_t color);

protected:

};

#endif //GFX_H

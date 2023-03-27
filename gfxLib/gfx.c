#include "gfx.h"

gfxScreenProperties_t gfxSreenProp;

void gfx_init(int screenX, int screenY) {
	gfxSreenProp.width = screenX;
	gfxSreenProp.height = screenY;
}

//// funkcje podstawowe definiowane na zewnątrz
//__weak void clearScr(uint16_t color) {
//	//czyszczenie ekranu
//}
//
//__weak void drawPixel(int32_t x, int32_t y, uint16_t color) {
//	// rysowanie pixela
//}
//
//__weak void drawHLine(int32_t x1, int32_t x2, int32_t y, uint16_t color) {
//	// rysowanie poziomej linii
//}
//
//__weak void drawVLine(int32_t x, int32_t y1, int32_t y2, uint16_t color) {
//	// rysowanie pionowej linii
//}
//
//__weak void copyBuffer(uint16_t *buffer, int32_t x, int32_t y, uint32_t heigh, uint32_t width) {
//	// kopiowanie fragmentu pamięcia na ekran
//}


#include "gfx.h"

Gfx::Gfx() {
}

void Gfx::init(scrOrient_t scrOrient, int screenX, int screenY) {
	if ((screenX > 0) && (screenY > 0)) {
		width = screenX;
		height = screenY;
	}
	drvInit(scrOrient);
	scrWidth = width;
	scrHeight = height;
}

void Gfx::clr(uint16_t color){
	clearScr(color);
}




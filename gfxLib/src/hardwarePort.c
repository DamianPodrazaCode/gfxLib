#include "hardwarePort.h"

__weak void setPixel(int x, int y, unsigned short color) {}
__weak void hLine(int x0, int x1, int y, unsigned short color) {}
__weak void vLine(int x, int y0, int y1, unsigned short color) {}
__weak void copyBuffer(unsigned short* buffer, int x, int y, int heigh, int width) {}

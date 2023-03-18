#include "hardwarePort.h"

__weak void setPixel(unsigned short x, unsigned short y, unsigned short color) {}
__weak void hLine(unsigned short x1, unsigned short x2, unsigned short y, unsigned short color) {}
__weak void vLine(unsigned short x, unsigned short y1, unsigned short y2, unsigned short color) {} 
__weak void copyBuffer(unsigned short* buffer, unsigned short x, unsigned short y, unsigned short heigh, unsigned short width) {}

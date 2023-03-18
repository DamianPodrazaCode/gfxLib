#ifndef HARDWARE_PORT_H
#define HARDWARE_PORT_H

#ifndef __weak
#define __weak   __attribute__((weak))
#endif // __weak 

void setPixel(int x, int y, unsigned short color);
void hLine(int x0, int x1, int y, unsigned short color);
void vLine(int x, int y0, int y1, unsigned short color);
void copyBuffer(unsigned short* buffer, int x, int y, int heigh, int width);

#endif //HARDWARE_PORT_H

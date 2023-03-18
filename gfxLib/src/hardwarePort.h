#ifndef HARDWARE_PORT_H
#define HARDWARE_PORT_H

#ifndef __weak
#define __weak   __attribute__((weak))
#endif // __weak 

void setPixel(unsigned short x, unsigned short y, unsigned short color);
void hLine(unsigned short x1, unsigned short x2, unsigned short y, unsigned short color);
void vLine(unsigned short x, unsigned short y1, unsigned short y2, unsigned short color);
void copyBuffer(unsigned short* buffer, unsigned short x, unsigned short y, unsigned short heigh, unsigned short width);

#endif //HARDWARE_PORT_H

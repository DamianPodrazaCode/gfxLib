#ifndef HARDWARE_PORT_H
#define HARDWARE_PORT_H

#ifndef __weak
#define __weak   __attribute__((weak))
#endif // __weak 

void setPixel(unsigned short x, unsigned short y, unsigned short color);

#endif //HARDWARE_PORT_H

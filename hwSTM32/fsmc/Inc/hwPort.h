#ifndef HWPORT_H_
#define HWPORT_H_

#include "main.h"
#include "fsmc.h"
#include "dma.h"

#include <stdbool.h>
#include <stdlib.h>

class HwPort {
public:
	HwPort();

private:

protected:
	void writeCMD(uint16_t cmd);
	void writeDATA(uint16_t data);
	void lcdBlOn();
	void lcdBlOff();
	void lcdRstHI();
	void lcdRstLOW();
	void lcdDelayMs(uint32_t ms);
};

#endif /* HWPORT_H_ */

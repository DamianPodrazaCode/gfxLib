#ifndef MAIN_H
#define MAIN_H

#define FSMC_LCD_8bit
//#define FSMC_LCD_16bit

#include "stm32f2xx_hal.h"
#include "irqHandlers/stm32_it.h"
#include "led/ledConfig.h"
#include "clocks/clocks.h"
//#include "stm32f2xx_nucleo_144.h"
#include "fsmc/fsmcInit.h"

void Error_Handler(void);

#endif // MAIN_H
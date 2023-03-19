#ifndef FSMC_INIT_H
#define FSMC_INIT_H

#include "main.h"

#define LCD_RS_DC_Pin GPIO_PIN_11
#define LCD_RS_DC_GPIO_Port GPIOD
#define LCD_RD_Pin GPIO_PIN_4
#define LCD_RD_GPIO_Port GPIOD
#define LCD_WR_Pin GPIO_PIN_5
#define LCD_WR_GPIO_Port GPIOD
#define LCD_CS_Pin GPIO_PIN_7
#define LCD_CS_GPIO_Port GPIOD

extern SRAM_HandleTypeDef hsram1;
void fsmcInit(void);


#endif //FSMC_INIT_H

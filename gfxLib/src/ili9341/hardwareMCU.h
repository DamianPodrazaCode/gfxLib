/*
 * hardwareMCU.h
 *
 *  Created on: Dec 31, 2022
 *      Author: ZoMbiE
 */

#ifndef HARDWAREMCU_H_
#define HARDWAREMCU_H_

#include "main.h"
#include <stdbool.h>

#define lcdBlOn() HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET)
#define lcdBlOff() HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_RESET)
#define lcdRstHI() HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET)
#define lcdRstLOW() HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET)

void initExtraHardware();
void writeCMD(uint16_t cmd);
void writeDATA(uint16_t data);
bool writeBUFFER(uint32_t buffer, uint32_t size);

#endif /* HARDWAREMCU_H_ */

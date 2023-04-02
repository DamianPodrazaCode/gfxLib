#include "hwPort.h"

#define ADDR_CMD (0x60000000) //LCD_RS=0
#define ADDR_RAM (0x60020000) //LCD_RS=1, LINIA A16 przy 16bit

HwPort::HwPort() {
}

void HwPort::writeCMD(uint16_t cmd) {
	*(__IO uint16_t*) (ADDR_CMD) = cmd;
}

void HwPort::writeDATA(uint16_t data) {
	*(__IO uint16_t*) (ADDR_RAM) = data;
}

void HwPort::lcdBlOn() {
	HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET);
}

void HwPort::lcdBlOff() {
	HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_RESET);
}

void HwPort::lcdRstHI() {
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
}

void HwPort::lcdRstLOW() {
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET);
}

void HwPort::lcdDelayMs(uint32_t ms) {
	HAL_Delay(ms);
}

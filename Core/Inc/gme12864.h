#ifndef __GME12864_H
#define __GME12864_H

#include "stm32f4xx_hal.h"

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

extern I2C_HandleTypeDef hi2c1;   // change if using hi2c2

void OLED_Init(void);
void OLED_UpdateScreen(void);
void OLED_Clear(void);
void OLED_DrawPixel(uint8_t x, uint8_t y, uint8_t color);
void OLED_DrawSquare(uint8_t x, uint8_t y, uint8_t size);

#endif

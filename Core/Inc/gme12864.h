#ifndef GME12864_H
#define GME12864_H

#include <stdint.h>

/* OLED display size */
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_ADDR 0x78  // Change if your module has a different I2C address

/* Basic OLED functions */
void OLED_Init(void);
void OLED_Clear(void);
void OLED_UpdateScreen(void);
void OLED_DrawPixel(uint8_t x, uint8_t y, uint8_t color);

/* Draw a 16x16 bitmap at (x,y) */
void OLED_DrawBitmap(uint8_t x, uint8_t y, const uint8_t bitmap[16][16]);

#endif

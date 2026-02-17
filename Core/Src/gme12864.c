#include "gme12864.h"
#include <string.h>

#define OLED_ADDR 0x78   // 0x3C << 1

static uint8_t OLED_Buffer[OLED_WIDTH * OLED_HEIGHT / 8];

static void OLED_WriteCommand(uint8_t cmd)
{
    uint8_t data[2];
    data[0] = 0x00;
    data[1] = cmd;
    HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDR, data, 2, HAL_MAX_DELAY);
}

static void OLED_WriteData(uint8_t* buffer, size_t buff_size)
{
    uint8_t data[buff_size + 1];
    data[0] = 0x40;
    memcpy(&data[1], buffer, buff_size);
    HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDR, data, buff_size + 1, HAL_MAX_DELAY);
}

void OLED_Init(void)
{
    HAL_Delay(100);

    OLED_WriteCommand(0xAE); // display off
    OLED_WriteCommand(0x20); // memory mode
    OLED_WriteCommand(0x00); // horizontal addressing
    OLED_WriteCommand(0xAF); // display on
}

void OLED_Clear(void)
{
    memset(OLED_Buffer, 0, sizeof(OLED_Buffer));
}

void OLED_UpdateScreen(void)
{
    for(uint8_t page = 0; page < 8; page++)
    {
        OLED_WriteCommand(0xB0 + page);
        OLED_WriteCommand(0x00);
        OLED_WriteCommand(0x10);

        OLED_WriteData(&OLED_Buffer[OLED_WIDTH * page], OLED_WIDTH);
    }
}

void OLED_DrawPixel(uint8_t x, uint8_t y, uint8_t color)
{
    if(x >= OLED_WIDTH || y >= OLED_HEIGHT) return;

    if(color)
        OLED_Buffer[x + (y / 8) * OLED_WIDTH] |= 1 << (y % 8);
    else
        OLED_Buffer[x + (y / 8) * OLED_WIDTH] &= ~(1 << (y % 8));
}

void OLED_DrawSquare(uint8_t x, uint8_t y, uint8_t size)
{
    for(uint8_t i = 0; i < size; i++)
    {
        for(uint8_t j = 0; j < size; j++)
        {
            OLED_DrawPixel(x + i, y + j, 1);
        }
    }
}

#include "input.h"
#include "game.h"
#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart2;

void Input_Process(void)
{
    uint8_t c;
    if (HAL_UART_Receive(&huart2, &c, 1, 10) == HAL_OK)
    {
        Game_HandleInput(c);
    }
}

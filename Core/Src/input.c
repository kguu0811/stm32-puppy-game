#include "input.h"
#include "gme12864.h" // for OLED_WIDTH, OLED_HEIGHT
#include <stdio.h>    // for sprintf

// Define global square variables
uint8_t square_x = 64;
uint8_t square_y = 32;
const uint8_t square_size = 5;
const uint8_t step = 3;

void Input_Init(void)
{
    // Nothing needed for now
}

void Process_Input(uint8_t rx_byte, char *msg)
{
    // Clear OLED buffer
    OLED_Clear();

    // Update square coordinates based on WASD input
    switch(rx_byte)
    {
        case 'w': // up
            if (square_y >= step) square_y -= step;
            else square_y = 0;
            sprintf(msg, "Up\n");
            break;
        case 's': // down
            if (square_y + square_size + step < OLED_HEIGHT)
                square_y += step;
            else square_y = OLED_HEIGHT - square_size;
            sprintf(msg, "Down\n");
            break;
        case 'a': // left
            if (square_x >= step) square_x -= step;
            else square_x = 0;
            sprintf(msg, "Left\n");
            break;
        case 'd': // right
            if (square_x + square_size + step < OLED_WIDTH)
                square_x += step;
            else square_x = OLED_WIDTH - square_size;
            sprintf(msg, "Right\n");
            break;
        default:
            sprintf(msg, "Unknown: %c\n", rx_byte);
    }

    // Draw square at new position
    OLED_DrawSquare(square_x, square_y, square_size);
    OLED_UpdateScreen();
}

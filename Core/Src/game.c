#include "game.h"
#include "bitmaps.h"
#include "gme12864.h"
#include "stm32f4xx_hal.h"
#include <stdlib.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

typedef enum {
    GAME_NORMAL,
    GAME_POO_EVENT,
    GAME_SLEEP_EVENT
} GameState;

static uint8_t puppy_x;
static uint8_t puppy_y;

static uint8_t poo_x;
static uint8_t poo_y;

static uint8_t sleep_x;
static uint8_t sleep_y;

static GameState game_state;
static uint32_t last_event_time;

/* AABB collision check */
static uint8_t collision(uint8_t x1, uint8_t y1,
                         uint8_t x2, uint8_t y2)
{
    return !(x1 + 16 <= x2 ||
             x2 + 16 <= x1 ||
             y1 + 16 <= y2 ||
             y2 + 16 <= y1);
}

void Game_Init(void)
{
    puppy_x = 40;
    puppy_y = 20;
    game_state = GAME_NORMAL;
    last_event_time = HAL_GetTick();
}

void Game_HandleInput(char c)
{
    /* Movement allowed if not in Sleep */
    if (game_state != GAME_SLEEP_EVENT)
    {
        if (c == 'w') puppy_y--;
        if (c == 's') puppy_y++;
        if (c == 'a') puppy_x--;
        if (c == 'd') puppy_x++;

        /* Clamp to screen */
        if (puppy_x > SCREEN_WIDTH - 16) puppy_x = SCREEN_WIDTH - 16;
        if (puppy_y > SCREEN_HEIGHT - 16) puppy_y = SCREEN_HEIGHT - 16;
    }

    /* Resolve poo */
    if (game_state == GAME_POO_EVENT && collision(puppy_x, puppy_y, poo_x, poo_y) && c == 'c')
    {
        game_state = GAME_NORMAL;
    }

    /* Resolve sleep */
    if (game_state == GAME_SLEEP_EVENT && c == 'z')
    {
        game_state = GAME_NORMAL;
    }
}

void Game_Update(void)
{
    /* Only spawn new event if no active event */
    if (game_state == GAME_NORMAL &&
        HAL_GetTick() - last_event_time > 5000)
    {
        last_event_time = HAL_GetTick();

        if (rand() % 2 == 0)
        {
            /* Spawn a poop at a random position */
            poo_x = rand() % (SCREEN_WIDTH - 16);
            poo_y = rand() % (SCREEN_HEIGHT - 16);
            game_state = GAME_POO_EVENT;
        }
        else
        {
            /* Spawn sleep next to puppy (top-left) */
            sleep_x = (puppy_x > 16) ? puppy_x - 16 : puppy_x + 16;
            sleep_y = (puppy_y > 16) ? puppy_y - 16 : puppy_y + 16;
            game_state = GAME_SLEEP_EVENT;
        }
    }
}

void Game_Draw(void)
{
    OLED_Clear();

    /* Draw puppy */
    OLED_DrawBitmap(puppy_x, puppy_y, puppy_bitmap);

    /* Draw active event */
    if (game_state == GAME_POO_EVENT)
        OLED_DrawBitmap(poo_x, poo_y, poo_bitmap);
    else if (game_state == GAME_SLEEP_EVENT)
        OLED_DrawBitmap(sleep_x, sleep_y, sleep_bitmap);

    OLED_UpdateScreen();
}

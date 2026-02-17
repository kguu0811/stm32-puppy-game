#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

// Square coordinates
extern uint8_t square_x;
extern uint8_t square_y;
extern const uint8_t square_size;
extern const uint8_t step;

// Initialize input module (if needed)
void Input_Init(void);

// Process a key press
// rx_byte: the received UART byte
// msg: string to store the direction for UART echo
void Process_Input(uint8_t rx_byte, char *msg);

#endif // INPUT_H

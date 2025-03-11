/************************************************************
 * Author      : Huda Hussam 
 * Date        : 2024
 ************************************************************/



#ifndef INC_BUTTONS_LEDS_H_
#define INC_BUTTONS_LEDS_H_
#include "main.h"
uint8_t scanButtonsAndToggleLEDs(void);
void debounceDelay(void);
void buttons_vars_update(uint8_t);
#define PRESSED 1
#define UNPRESSED 0
#endif /* INC_BUTTONS_LEDS_H_ */

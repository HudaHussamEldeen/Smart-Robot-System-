/************************************************************
 * Author      : Huda Hussam 
 * Date        : 2024
 ************************************************************/

#include "main.h"
#include "cmsis_os.h"

void debounceDelay(void)
{
	osDelay(100);  // Adjust the delay as needed
}

uint8_t scanButtonsAndToggleLEDs(void)
{
	uint8_t buttonState = 0;  // Initialize the button state variable

	if (HAL_GPIO_ReadPin(BUTTON_RIGHT_GPIO_Port, BUTTON_RIGHT_Pin) == GPIO_PIN_RESET)
	{
		debounceDelay();
		if (HAL_GPIO_ReadPin(BUTTON_RIGHT_GPIO_Port, BUTTON_RIGHT_Pin) == GPIO_PIN_RESET)
		{
			HAL_GPIO_TogglePin(GPIOD, LED_D_15_Pin);

			buttonState |= (1 << 0); // Set the bit corresponding to BUTTON_RIGHT
		}
	}

	if (HAL_GPIO_ReadPin(BUTTON_DOWN_GPIO_Port, BUTTON_DOWN_Pin) == GPIO_PIN_RESET)
	{
		debounceDelay();
		if (HAL_GPIO_ReadPin(BUTTON_DOWN_GPIO_Port, BUTTON_DOWN_Pin) == GPIO_PIN_RESET)
		{

			HAL_GPIO_TogglePin(GPIOD, LED_D_14_Pin);

			buttonState |= (1 << 1); // Set the bit corresponding to BUTTON_DOWN
		}
	}

	if (HAL_GPIO_ReadPin(BUTTON_LEFT_GPIO_Port, BUTTON_LEFT_Pin) == GPIO_PIN_RESET)
	{
		debounceDelay();
		if (HAL_GPIO_ReadPin(BUTTON_LEFT_GPIO_Port, BUTTON_LEFT_Pin) == GPIO_PIN_RESET)
		{
			HAL_GPIO_TogglePin(GPIOD, LED_D_13_Pin);

			buttonState |= (1 << 2); // Set the bit corresponding to BUTTON_LEFT
		}
	}

	if (HAL_GPIO_ReadPin(BUTTON_UP_GPIO_Port, BUTTON_UP_Pin) == GPIO_PIN_RESET)
	{
		debounceDelay();
		if (HAL_GPIO_ReadPin(BUTTON_UP_GPIO_Port, BUTTON_UP_Pin) == GPIO_PIN_RESET)
		{

			HAL_GPIO_TogglePin(GPIOD, LED_D_12_Pin);

			buttonState |= (1 << 3);  // Set the bit corresponding to BUTTON_UP
		}
	}

	if (HAL_GPIO_ReadPin(BUTTON_CANCEL_GPIO_Port, BUTTON_CANCEL_Pin) == GPIO_PIN_RESET)
	{
		debounceDelay();
		if (HAL_GPIO_ReadPin(BUTTON_CANCEL_GPIO_Port, BUTTON_CANCEL_Pin) == GPIO_PIN_RESET)
		{

			HAL_GPIO_TogglePin(GPIOC, LED_C_8_Pin);

			buttonState |= (1 << 4); // Set the bit corresponding to BUTTON_CANCEL
		}
	}

	if (HAL_GPIO_ReadPin(BUTTON_ENTER_GPIO_Port, BUTTON_ENTER_Pin) == GPIO_PIN_RESET)
	{
		debounceDelay();
		if (HAL_GPIO_ReadPin(BUTTON_ENTER_GPIO_Port, BUTTON_ENTER_Pin) == GPIO_PIN_RESET)
		{
			HAL_GPIO_TogglePin(GPIOB, LED_B_15_Pin);

			HAL_GPIO_TogglePin(GPIOB, LED_B_14_Pin);

			buttonState |= (1 << 5); // Set the bit corresponding to BUTTON_ENTER
		}
	}

	return buttonState;
}


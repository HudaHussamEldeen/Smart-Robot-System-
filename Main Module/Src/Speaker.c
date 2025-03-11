/************************************************************
 * Author      : Huda Hussam 
 * Date        : 2024
 ************************************************************/


#include"Speaker.h"
#include "main.h"
#include "dac.h"
#include "tim.h"
#include "math.h"
#include "cmsis_os.h"

float frequency = 100.0;  // Adjust the frequency as needed
uint32_t val = 0;
uint32_t x = 0;

// Note frequencies in Hz
#define NOTE_C4   262
#define NOTE_D4   294
#define NOTE_E4   330
#define NOTE_F4   349
#define NOTE_G4   392
#define NOTE_A4   440
#define NOTE_B4   494
#define NOTE_C5   523
#define NOTE_D5   587
#define NOTE_E5   659
#define NOTE_F5   698
#define NOTE_G5   784
#define NOTE_A5   880
#define NOTE_B5   988

volatile uint8_t toggle_state = 0; // State to toggle the DAC output

void TIM6_StartForFrequency(uint16_t frequency)
{
	uint32_t timer_period = HAL_RCC_GetPCLK1Freq() / (frequency * 2);

	// Configure TIM6 Period
	__HAL_TIM_SET_AUTORELOAD(&htim6, timer_period - 1);
	__HAL_TIM_SET_PRESCALER(&htim6, 0);

	// Start TIM6 in interrupt mode
	HAL_TIM_Base_Start_IT(&htim6);
}

// TIM6 Interrupt Handler

// Play a specific note
void PlayNote(uint16_t frequency, uint32_t duration)
{
	TIM6_StartForFrequency(frequency); // Start TIM6 with desired note frequency
	osDelay(duration);                 // Play the note for the specified duration
	HAL_TIM_Base_Stop_IT(&htim6);      // Stop TIM6 after the note
}

void OpenRingtone(void)
{
	Toggle_Output_Leds();

	PlayNote(NOTE_C5, 125); // C5
	PlayNote(NOTE_D5, 125); // D5
	PlayNote(NOTE_F5, 125); // F5
	PlayNote(NOTE_A5, 125); // A5

	Toggle_Output_Leds();
}

void MsgRingtone(void)
{
	Toggle_Output_Leds();

	PlayNote(NOTE_D5, 125); // D5
	PlayNote(NOTE_F5, 125); // F5
	PlayNote(NOTE_A5, 125); // A5

	Toggle_Output_Leds();
}


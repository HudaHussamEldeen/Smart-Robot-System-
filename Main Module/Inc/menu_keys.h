/************************************************************
 * Author      : Huda Hussam 
 * Date        : 2024
 ************************************************************/


#ifndef INC_MENU_KEYS_H_
#define INC_MENU_KEYS_H_
#include "main.h"
#include "KS0108.h"
#include "cmsis_os.h"
#include "can_module.h"
#include <string.h>
#include <stdio.h>
#include "usbd_cdc_if.h"

#define UP_BTN_STATE	(HAL_GPIO_ReadPin(BUTTON_UP_GPIO_Port, BUTTON_UP_Pin))
#define DOWN_BTN_STATE	( HAL_GPIO_ReadPin(BUTTON_DOWN_GPIO_Port, BUTTON_DOWN_Pin))
#define RIGHT_BTN_STATE	(HAL_GPIO_ReadPin(BUTTON_RIGHT_GPIO_Port, BUTTON_RIGHT_Pin))
#define LEFT_BTN_STATE	(HAL_GPIO_ReadPin(BUTTON_LEFT_GPIO_Port, BUTTON_LEFT_Pin))
#define ENTER_BTN_STATE	( HAL_GPIO_ReadPin(BUTTON_ENTER_GPIO_Port, BUTTON_ENTER_Pin))
#define CANCEL_BTN_STATE	(HAL_GPIO_ReadPin(BUTTON_CANCEL_GPIO_Port, BUTTON_CANCEL_Pin))

void button_scan();
void menu();
void MenuKeys_Init(void);
void IdHandle(void);
void MaxIdHanle(void);
void Z_Y_Id_scan(void);
void MaxDataHandle(void);
void DataForwardingHandle(void);


#define MAIN_PAGE              0
#define SELECT_PAGE            0
#define MANUAL_MODE            1
#define ARM_MANUALMODE         2
#define MOTOR_MANUALMODE       3
#define SENSORS_MANUALMODE     4
#define PENDULUM_MANUALMODE    5
#define INTELLIGENT_MANUALMODE 6
#define BlUETOOTH_MODE         7
#define CLOSING_PAGE           8

extern uint8_t Selected_Page;

typedef struct
{
	uint8_t Up;
	uint8_t Down;
	uint8_t Right;
	uint8_t Left;
	uint8_t Enter;
	uint8_t Cancel;

	uint8_t Page;
	uint8_t PrevPage;
	int8_t Y_Id;
	int8_t X_Id;
	int8_t Z_Id;

	uint8_t *PrevPagePtr;
	uint8_t *PagePtr;
	int8_t *Y_IdPtr;
	int8_t *X_IdPtr;
	int8_t *Z_IdPtr;

	uint8_t Max_Page_X_Id;
	uint8_t Max_Page_Y_Id;
	uint8_t Max_Page_Z_Id;

	uint8_t X_Step;
	uint8_t Y_Step;
	uint8_t Z_Step;

} Menu_Inputs;
extern Menu_Inputs Menu_btns;

typedef struct
{
	uint8_t Arm0Value;
	uint8_t Arm1Value;
	uint8_t Arm2Value;
	uint8_t Arm3Value;
	uint8_t Arm4Value;
	uint8_t Arm5Value;
	uint8_t Arm6Value;

	uint16_t StepperValue;
	uint8_t StepperDir;
	uint8_t ServoValue;
	uint8_t DCValue;
	uint8_t DCDIR;

	uint8_t Servo0Value;
	uint8_t Servo1Value;

	float A_Kp;
	float A_Kd;
	uint8_t A_SetPoint;

	float P_Kp;
	float P_Kd;
	uint8_t P_SetPoint;
    uint8_t Task;

	uint8_t Duty;
	uint8_t Movement;

} Menue_Data;

extern Menue_Data Module_Data;


#endif /* INC_MENU_KEYS_H_ */

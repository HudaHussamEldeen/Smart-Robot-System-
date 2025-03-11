/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>
#include "can_module.h"

#include "menu_keys.h"
#include "KS0108-STM32.h"

#include "Buttons_Leds.h"
#include"GLCD.h"

#include "Speaker.h"
#include "KS0108.h"
#include "Blu_Buffer.h"

#include "usbd_cdc_if.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern char company_logo[1024];

uint8_t TxBuffer[] = "Hello from BEDO RoboEX Main Module USB OTG \n";
uint8_t TxBufferLen = sizeof(TxBuffer);
char UsbReportBuffer[50];

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId ScanHandle;
osThreadId ActionHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

static void USB_Send_Report(const char *Str)
{
    if (Str != NULL)                                 // Check if input is valid
    {
        uint8_t StrLen = strlen(Str);                // Get the length of the string
        if (StrLen > 0)                              // Ensure non-zero length
        {
            CDC_Transmit_FS((uint8_t*)Str, StrLen);  // Transmit string over USB
        }
    }
}

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartScan(void const * argument);
void StartAction(void const * argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
	*ppxIdleTaskStackBuffer = &xIdleStack[0];
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
	/* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of Scan */
  osThreadDef(Scan, StartScan, osPriorityNormal, 0, 128);
  ScanHandle = osThreadCreate(osThread(Scan), NULL);

  /* definition and creation of Action */
  osThreadDef(Action, StartAction, osPriorityNormal, 0, 128);
  ActionHandle = osThreadCreate(osThread(Action), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartDefaultTask */

	GLCD_Initialize();
	GLCD_ClearScreen();
	GLCD_GoTo(0, 0);
	GLCD_Bitmap(company_logo, 0, 0, 128, 64);
	osDelay(1000);
	GLCD_ClearScreen();
	MenuKeys_Init();

	CDC_Transmit_FS(TxBuffer, TxBufferLen);
	/* Infinite loop */
	for (;;)
	{
		button_scan();
		menu();
	}
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartScan */
/**
 * @brief Function implementing the Scan thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartScan */
void StartScan(void const * argument)
{
  /* USER CODE BEGIN StartScan */

	Blu_UART_Init(&huart3);

	Module_Data.Arm0Value = 90;
	Module_Data.Arm1Value = 90;
	Module_Data.Arm2Value = 90;
	Module_Data.Arm3Value = 90;
	Module_Data.Arm4Value = 90;
	Module_Data.Arm5Value = 0;

	Module_Data.Servo0Value = 90;
	Module_Data.Servo1Value = 90;
	/* Infinite loop */
	for (;;)
	{
		osDelay(1000000);
	}
  /* USER CODE END StartScan */
}

/* USER CODE BEGIN Header_StartAction */
/**
 * @brief Function implementing the Action thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartAction */
void StartAction(void const * argument)
{
  /* USER CODE BEGIN StartAction */
	//CAN1
	CanInit(&hcan1);
	CanInit(&hcan2);
	CanFilterConfig();
	CanFilterUpdate(&hcan1);
	CanFilterUpdate(&hcan2);
	// Play a simple melody
	OpenRingtone();
	Module_Data.P_SetPoint = 30;
	Module_Data.A_SetPoint = 180;
	Module_Data.Task = 'P';
	/* Infinite loop */
	for (;;)
	{
		if (CAN_ACK_Flag == 1)
		{
			MsgRingtone();
		    snprintf(UsbReportBuffer, sizeof(UsbReportBuffer), "CAN MSG Forwarded: %c %c %d %d %d %d %d %d\r\n",
			    	TxData[0], TxData[1], TxData[2], TxData[3],
			    	TxData[4], TxData[5], TxData[6], TxData[7]);
			USB_Send_Report(UsbReportBuffer);
			CAN_ACK_Flag = 0;
		}
		osDelay(50);
	}
  /* USER CODE END StartAction */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

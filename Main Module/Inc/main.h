/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUTTON_DOWN_Pin GPIO_PIN_5
#define BUTTON_DOWN_GPIO_Port GPIOE
#define GLCD_DB7_Pin GPIO_PIN_0
#define GLCD_DB7_GPIO_Port GPIOC
#define GLCD_CS1_Pin GPIO_PIN_1
#define GLCD_CS1_GPIO_Port GPIOC
#define GLCD_RST_Pin GPIO_PIN_2
#define GLCD_RST_GPIO_Port GPIOC
#define GLCD_CS2_Pin GPIO_PIN_3
#define GLCD_CS2_GPIO_Port GPIOC
#define GLCD_DB6_Pin GPIO_PIN_2
#define GLCD_DB6_GPIO_Port GPIOA
#define GLCD_DB5_Pin GPIO_PIN_3
#define GLCD_DB5_GPIO_Port GPIOA
#define GLCD_DB4_Pin GPIO_PIN_5
#define GLCD_DB4_GPIO_Port GPIOA
#define GLCD_DB3_Pin GPIO_PIN_6
#define GLCD_DB3_GPIO_Port GPIOA
#define GLCD_DB2_Pin GPIO_PIN_7
#define GLCD_DB2_GPIO_Port GPIOA
#define GLCD_DB1_Pin GPIO_PIN_4
#define GLCD_DB1_GPIO_Port GPIOC
#define GLCD_DB0_Pin GPIO_PIN_5
#define GLCD_DB0_GPIO_Port GPIOC
#define GLCD_RW_Pin GPIO_PIN_8
#define GLCD_RW_GPIO_Port GPIOE
#define GLCD_EN_Pin GPIO_PIN_10
#define GLCD_EN_GPIO_Port GPIOE
#define Test_clk_Pin GPIO_PIN_13
#define Test_clk_GPIO_Port GPIOE
#define BUTTON_LEFT_Pin GPIO_PIN_14
#define BUTTON_LEFT_GPIO_Port GPIOE
#define LED_B_14_Pin GPIO_PIN_14
#define LED_B_14_GPIO_Port GPIOB
#define LED_B_15_Pin GPIO_PIN_15
#define LED_B_15_GPIO_Port GPIOB
#define SPI3_CS_Pin GPIO_PIN_11
#define SPI3_CS_GPIO_Port GPIOD
#define LED_D_12_Pin GPIO_PIN_12
#define LED_D_12_GPIO_Port GPIOD
#define LED_D_13_Pin GPIO_PIN_13
#define LED_D_13_GPIO_Port GPIOD
#define LED_D_14_Pin GPIO_PIN_14
#define LED_D_14_GPIO_Port GPIOD
#define LED_D_15_Pin GPIO_PIN_15
#define LED_D_15_GPIO_Port GPIOD
#define LED_C_8_Pin GPIO_PIN_8
#define LED_C_8_GPIO_Port GPIOC
#define GLCD_RS_Pin GPIO_PIN_0
#define GLCD_RS_GPIO_Port GPIOD
#define HC05_EN_Pin GPIO_PIN_1
#define HC05_EN_GPIO_Port GPIOD
#define BUTTON_CANCEL_Pin GPIO_PIN_4
#define BUTTON_CANCEL_GPIO_Port GPIOD
#define BUTTON_ENTER_Pin GPIO_PIN_7
#define BUTTON_ENTER_GPIO_Port GPIOD
#define BUTTON_UP_Pin GPIO_PIN_0
#define BUTTON_UP_GPIO_Port GPIOE
#define BUTTON_RIGHT_Pin GPIO_PIN_1
#define BUTTON_RIGHT_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

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

extern uint8_t MainModuleCanRecivedData[8];
extern uint8_t ArmModuleCanRecivedData[8];
extern uint8_t PendalluamModuleCanRecivedData[8];
extern uint8_t BrainModuleCanRecivedData[8];
extern uint8_t MotorModuleCanRecivedData[8];
extern uint8_t SensorsAcuatorsModuleCanRecivedData[8];
extern CAN_TxHeaderTypeDef TxHeader;
extern CAN_RxHeaderTypeDef RxHeader;
extern uint32_t TxMailbox;
extern uint8_t Uart_RX_Flag;
extern uint8_t CAN_ACK_Flag;
#define Blu_buf_size 22
extern uint8_t t_buf[Blu_buf_size];
extern uint8_t r_buf[Blu_buf_size];
extern uint8_t Blu_data[Blu_buf_size] ;

extern volatile uint8_t toggle_state;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

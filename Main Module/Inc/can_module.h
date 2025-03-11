/************************************************************
 * Author      : Huda Hussam 
 * Date        : 2024
 ************************************************************/




#ifndef INC_CAN_MODULE_H_
#define INC_CAN_MODULE_H_
#include "main.h"
#include "can.h"


#define ROBOT_MAIN_MODULE_CAN	             0x100
#define ROBOT_ARM_MODULE_CAN	             0x101
#define ROBOT_PENDALUAM_MODULE_CAN	         0x102
#define ROBOT_BRAIN_MODULE_CAN	             0x105
#define ROBOT_MOTOR_STUDY_MODULE_CAN	     0x104
#define ROBOT_SENSORS_ACUATORS_MODULE_CAN	 0x103

extern uint8_t MainModuleCanRecivedData[8];
extern uint8_t ArmModuleCanRecivedData[8];
extern uint8_t PendalluamModuleCanRecivedData[8];
extern uint8_t BrainModuleCanRecivedData[8];
extern uint8_t MotorModuleCanRecivedData[8];
extern uint8_t SensorsAcuatorsModuleCanRecivedData[8];



extern CAN_TxHeaderTypeDef TxHeader2;
extern CAN_RxHeaderTypeDef RxHeader2;
extern uint32_t 		   TxMailbox2;
extern uint8_t 			   TxData2[8];
extern uint8_t 			   RxData2[8];
extern uint8_t             BrainModuleCanRecivedData2[8];
extern uint8_t             ArmModuleCanRecivedData2[8];
extern uint8_t             SensorsAcuatorsModuleCanRecivedData2[8];
extern uint8_t             PendalluamModuleCanRecivedData2[8];
extern uint8_t             MotorModuleCanRecivedData2[8];
extern uint8_t             MainModuleCanRecivedData2[8];


extern CAN_TxHeaderTypeDef TxHeader;
extern CAN_RxHeaderTypeDef RxHeader;
extern uint32_t            TxMailbox;
extern uint8_t             TxData[8];
extern uint8_t 			   RxData[8];

void CopyArray(uint8_t *arr1, uint8_t *arr2);
void CanSendMessage(uint8_t *Data);
void CanFilterConfig(void);
void CanFilterUpdate(CAN_HandleTypeDef *hcan);
void CanInit(CAN_HandleTypeDef *hcan);
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);

#endif /* INC_CAN_MODULE_H_ */

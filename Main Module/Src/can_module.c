/************************************************************
 * Author      : Huda Hussam 
 * Date        : 2024
 ************************************************************/



#include "can_module.h"
#include "Speaker.h"

CAN_FilterTypeDef   canfilterconfig;
CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;
uint32_t            TxMailbox;
uint16_t            CanId =  ROBOT_MAIN_MODULE_CAN;
uint8_t 			TxData[8];
uint8_t 			RxData[8];
uint8_t 			MainModuleCanRecivedData[8];
uint8_t				ArmModuleCanRecivedData[8];
uint8_t 			PendalluamModuleCanRecivedData[8];
uint8_t 			BrainModuleCanRecivedData[8];
uint8_t 			MotorModuleCanRecivedData[8];
uint8_t 			SensorsAcuatorsModuleCanRecivedData[8];


CAN_FilterTypeDef   canfilterconfig2;
CAN_TxHeaderTypeDef TxHeader2;
CAN_RxHeaderTypeDef RxHeader2;
uint32_t            TxMailbox2;
uint8_t             TxData2[8];
uint8_t             RxData2[8];
uint8_t             BrainModuleCanRecivedData2[8];
uint8_t             ArmModuleCanRecivedData2[8];
uint8_t             SensorsAcuatorsModuleCanRecivedData2[8];
uint8_t             PendalluamModuleCanRecivedData2[8];
uint8_t             MotorModuleCanRecivedData2[8];
uint8_t             MainModuleCanRecivedData2[8];

static void CAN_Check_Ack(void)
{
	switch (RxHeader.StdId)
		{
			case ROBOT_ARM_MODULE_CAN:
				 CopyArray(RxData, ArmModuleCanRecivedData);
				 if (RxData[0] == 'R' && RxData[1] == 'A' && RxData[2] == 'A')
				 {
					 CAN_ACK_Flag = 1;
				 }
				 break;
			case ROBOT_PENDALUAM_MODULE_CAN:
				 CopyArray(RxData, PendalluamModuleCanRecivedData);
				 if (RxData[0] == 'P' && RxData[1] == 'R' && RxData[2] == 'A')
				 {
					 CAN_ACK_Flag = 1;
				 }
				 break;
		    case ROBOT_BRAIN_MODULE_CAN:
				 CopyArray(RxData, BrainModuleCanRecivedData);
				 if (RxData[0] == 'R' && RxData[1] == 'B' && RxData[2] == 'A')
				 {
					 CAN_ACK_Flag = 1;
				 }
				 break;
			case ROBOT_MOTOR_STUDY_MODULE_CAN:
				 CopyArray(RxData, MotorModuleCanRecivedData);
				 if (RxData[0] == 'M' && RxData[1] == 'S' && RxData[2] == 'A')
				 {
					 CAN_ACK_Flag = 1;
				 }
				 break;
			case ROBOT_SENSORS_ACUATORS_MODULE_CAN:
				 CopyArray(RxData, SensorsAcuatorsModuleCanRecivedData);
				 if (RxData[0] == 'S' && RxData[1] == 'A' && RxData[2] == 'A')
				 {
					 CAN_ACK_Flag = 1;
				 }
				 break;

			default:
				 break;
		}
}

void CanSendMessage(uint8_t *Data)
{
	HAL_CAN_AddTxMessage(&hcan1, &TxHeader, Data, &TxMailbox);
	HAL_CAN_AddTxMessage(&hcan2, &TxHeader, Data, &TxMailbox);
}

void CanFilterConfig(void)
{
	canfilterconfig.FilterActivation 	   = CAN_FILTER_ENABLE;
	canfilterconfig.FilterBank             = 27;
	canfilterconfig.FilterFIFOAssignment   = CAN_RX_FIFO0;
	canfilterconfig.FilterIdHigh           = 0x100 << 5;
	canfilterconfig.FilterIdLow            = 0x0000;
	canfilterconfig.FilterMaskIdHigh       = 0x100 << 5;
	canfilterconfig.FilterMaskIdLow        = 0x0000;
	canfilterconfig.FilterMode             = CAN_FILTERMODE_IDMASK;
	canfilterconfig.FilterScale            = CAN_FILTERSCALE_32BIT;
	canfilterconfig.SlaveStartFilterBank   = 0;
	//HAL_CAN_ConfigFilter(&hcan1, &canfilterconfig);
}

void CanFilterConfig2(void)
{
	canfilterconfig2.FilterActivation      = CAN_FILTER_ENABLE;
	canfilterconfig2.FilterBank            = 27;
	canfilterconfig2.FilterFIFOAssignment  = CAN_RX_FIFO0;
	canfilterconfig2.FilterIdHigh          = 0x100 << 5;
	canfilterconfig2.FilterIdLow		   = 0x0000;
	canfilterconfig2.FilterMaskIdHigh      = 0x100 << 5;
	canfilterconfig2.FilterMaskIdLow       = 0x0000;
	canfilterconfig2.FilterMode            = CAN_FILTERMODE_IDMASK;
	canfilterconfig2.FilterScale           = CAN_FILTERSCALE_32BIT;
	canfilterconfig2.SlaveStartFilterBank  = 14;
	//HAL_CAN_ConfigFilter(&hcan1, &canfilterconfig);
}

void CanFilterUpdate(CAN_HandleTypeDef *hcan)
{
	if (hcan == &hcan1)
		HAL_CAN_ConfigFilter(hcan, &canfilterconfig);
	if (hcan == &hcan2)
		HAL_CAN_ConfigFilter(hcan, &canfilterconfig2);
}

void CanInit(CAN_HandleTypeDef *hcan)
{
	HAL_CAN_Start(hcan);
	HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
	TxHeader.DLC                = 8;
	TxHeader.ExtId              = 0;
	TxHeader.IDE                = CAN_ID_STD;
	TxHeader.RTR                = CAN_RTR_DATA;
	TxHeader.StdId              = CanId;
	TxHeader.TransmitGlobalTime = DISABLE;
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if (hcan == &hcan1)
	{
		HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, RxData);

		if (RxHeader.DLC == 8)
		{
			if (CanId == ROBOT_MAIN_MODULE_CAN)
			{
				CAN_Check_Ack();
			}
			else
			{
				if (RxHeader.StdId == ROBOT_MAIN_MODULE_CAN)
				{
					CopyArray(RxData, MainModuleCanRecivedData);
				}
			}
			RxHeader.DLC = 0;
		}
		//TODO: Clear ACK
	}
	else if (hcan == &hcan2)
	{
		HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &RxHeader, RxData);

		if (CanId == ROBOT_MAIN_MODULE_CAN)
		{
			CAN_Check_Ack();
		}
		else
		{
			if (RxHeader.StdId == ROBOT_SENSORS_ACUATORS_MODULE_CAN)
			{
				CopyArray(RxData2, SensorsAcuatorsModuleCanRecivedData2);
			}
		}
		RxHeader2.DLC = 0;
		//TODO: Clear ACK
	}
}

void CopyArray(uint8_t *arr1, uint8_t *arr2)
{
	for (int i = 0; i < 8; i++)
	{
		arr2[i] = arr1[i];
	}
}

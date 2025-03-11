/************************************************************
 * Author      : Huda Hussam 
 * Date        : 2024
 ************************************************************/



#ifndef INC_BLU_BUFFER_H_
#define INC_BLU_BUFFER_H_

#include "main.h"
#include "usart.h"
#include <string.h>
#include <stdlib.h>
#include "can_module.h"
#include  "menu_keys.h"
void GetBlutoothData(void);

void Blu_UART_Init(UART_HandleTypeDef *huart);
void Blu_Buf_transmit(uint8_t *txbuffer,UART_HandleTypeDef *huart);

void CopyBluArray(uint8_t *source, uint8_t *destination, size_t size) ;

void clear_buffer(uint8_t *buffer, uint8_t size);

#endif /* INC_BLU_BUFFER_H_ */

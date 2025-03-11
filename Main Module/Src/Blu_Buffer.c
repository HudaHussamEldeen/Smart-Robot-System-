/************************************************************
 * Author      : Huda Hussam 
 * Date        : 2024
 ************************************************************/


#include "Blu_Buffer.h"
#include "main.h"

uint8_t t_buf[Blu_buf_size];
uint8_t r_buf[Blu_buf_size];
uint8_t Blu_data[Blu_buf_size];

void GetBlutoothData(void)
{
	if ((r_buf[0] != '\0') || (r_buf[1] != '\0') || (r_buf[2] != '\0')
	 || (r_buf[3] != '\0') || (r_buf[4] != '\0') || (r_buf[5] != '\0'))
	{
		for (int m = 0; m < Blu_buf_size; m++)
		{
			if ((r_buf[m] == 'E'))
			{
				for (int j = 0; j < Blu_buf_size; j++)
				{
					if ((r_buf[j] == '$'))
					{
						if (abs(m - j == 19))
						{
							HAL_UART_DMAPause(&huart3);

							if (j + 4 < Blu_buf_size)
							{
								Blu_data[0] = r_buf[j + 4];	//no of samples
							}
							else
							{
								Blu_data[0] = r_buf[j + 4 - Blu_buf_size];
							}
							if (j + 5 < Blu_buf_size)
							{
								Blu_data[1] = r_buf[j + 5];	//hs_input config
							}
							else
							{
								Blu_data[1] = r_buf[j + 5 - Blu_buf_size];
							}
							if (j + 7 < Blu_buf_size)
							{
								Blu_data[2] = r_buf[j + 7];	//data 0
							}
							else
							{
								Blu_data[2] = r_buf[j + 7 - Blu_buf_size];
							}
							if (j + 9 < Blu_buf_size)
							{
								Blu_data[3] = r_buf[j + 9];
							}
							else
							{
								Blu_data[3] = r_buf[j + 9 - Blu_buf_size];
							}
							if (j + 11 < Blu_buf_size)
							{
								Blu_data[4] = r_buf[j + 11];
							}
							else
							{
								Blu_data[4] = r_buf[j + 11 - Blu_buf_size];
							}
							if (j + 13 < Blu_buf_size)
							{
								Blu_data[5] = r_buf[j + 13];
							}
							else
							{
								Blu_data[5] = r_buf[j + 13 - Blu_buf_size];
							}
							if (j + 15 < Blu_buf_size)
							{
								Blu_data[6] = r_buf[j + 15];
							}
							else
							{
								Blu_data[6] = r_buf[j + 15 - Blu_buf_size];
							}
							if (j + 17 < Blu_buf_size)
							{
								Blu_data[7] = r_buf[j + 17];
							}
							else
							{
								Blu_data[7] = r_buf[j + 17 - Blu_buf_size];
							}

							m = 22;
							clear_buffer(r_buf, m);
							HAL_UART_DMAResume(&huart3);

							clear_buffer(TxData,sizeof(TxData));

							TxData[0] = Blu_data[0];
							TxData[1] = Blu_data[1];
							TxData[2] = Blu_data[2];
							TxData[3] = Blu_data[3];
							TxData[4] = Blu_data[4];
							TxData[5] = Blu_data[5];
							TxData[6] = Blu_data[6];
							TxData[7] = Blu_data[7];

							CanSendMessage(TxData);
							break;
						}
						else
						{
							HAL_UART_DMAStop(&huart3);
							HAL_UART_Receive_DMA(&huart3, r_buf, Blu_buf_size);
						}
					}
				}
			}
		}

	}
}

void extractDataWithoutCommas(char *input, uint8_t *output, size_t outputSize)
{
	size_t inputLen = strlen(input);
	size_t dataIndex = 0;

	for (size_t i = 0; i < inputLen; i++)
	{
		if (dataIndex < outputSize)
		{
			if (input[i] != ',')
			{
				// Convert character to integer and store in the output array
				output[dataIndex++] = input[i] - '0';
			}
		}
		else
		{
			// Output buffer is full, break the loop
			break;
		}
	}
}

void CopyBluArray(uint8_t *source, uint8_t *destination, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		destination[i] = source[i];
	}
}

void Blu_UART_Init(UART_HandleTypeDef *huart)
{
	HAL_GPIO_WritePin(HC05_EN_GPIO_Port, HC05_EN_Pin, GPIO_PIN_SET);
	HAL_UART_Receive_DMA(huart, r_buf, Blu_buf_size);
}

void Blu_Buf_transmit(uint8_t *txbuffer, UART_HandleTypeDef *huart)
{
	HAL_UART_Transmit_DMA(huart, txbuffer, Blu_buf_size);

}

void clear_buffer(uint8_t *buffer, uint8_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		buffer[i] = 0;
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (Selected_Page == BlUETOOTH_MODE)
	{
		Uart_RX_Flag = 1;
		GetBlutoothData();
		Menu_btns.Page = BlUETOOTH_MODE;
	}

	HAL_UART_Receive_DMA(&huart3, r_buf, Blu_buf_size);
}

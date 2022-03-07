/******************************************************
 * FileName:      uart.c
 * Company:       ????
 * Date:           2016/07/08  20:02
 * Description:    Lobot???????????,??stc89c52rc??,
 *                  ??????????????????????
 *                  @@????:????????????9600???@@
 *****************************************************/
#include "uart.h"
#include "LobotSerialServo.h"

#include <string.h>
void uartInit() //波特率115200
{
	PCON &= 0x7F;		//??????
	SCON = 0x50;		//8???,?????
	AUXR |= 0x04;		//???????????Fosc,?1T
	BRT = 0xFD;		//?????????????
	AUXR |= 0x01;		//??1?????????????????
	AUXR |= 0x10;		//??????????
	ES = 1;           //??Uart??
	EA = 1;           //???
}


uint8_t busy = 0;   //???????

/*********************************************************************************
 * Function:    uartWriteByte
 * Description:??????????
 * Parameters:   dat:????
 * Return:       ???
 * Others:
 **********************************************************************************/
void uartWriteByte(uint8_t dat)
{
	while (busy);
	busy = 1;
	SBUF = dat;
}

/*********************************************************************************
 * Function:    uartWriteBuf
 * Description:??????
 * Parameters:   buf:???????,len:??????
 * Return:       ???
 * Others:
 **********************************************************************************/
void uartWriteBuf(uint8_t *buf, uint8_t len)
{
	ES = 1;
	while (len--) {
		while (busy);
		busy = 1;
		SBUF = *buf++;
	}
}

/*********************************************************************************
 * Function:  receiveHandle
 * Description: ??????,??????,????
 * Parameters:   ?????
 * Return:       ???
 * Others:
 **********************************************************************************/

uint8_t UART_RX_BUF[24];
bool isUartRxCompleted = false;

void receiveHandle(void) interrupt 4
{
	uint8_t rx;
	static bool isGotFrameHeader = false;
	static uint8_t frameHeaderCount = 0;
	static uint8_t dataLength = 2;
	static uint8_t dataCount = 0;
	
	if (RI) {  //????
		RI = 0;  //清楚标识
		rx = SBUF;   //读取接收寄存器
		
		if(!isGotFrameHeader)
		{
			if(rx == 0x55)
			{
				frameHeaderCount++;
				if(frameHeaderCount == 2)
				{
					frameHeaderCount = 0;
					isGotFrameHeader = true;
					dataCount = 1;
				}
			}
			else
			{
				isGotFrameHeader = false;
				dataCount = 0;
				frameHeaderCount = 0;
			}
		}
		if(isGotFrameHeader)
		{
			UART_RX_BUF[dataCount] = rx;
			if(dataCount == 3)
			{
				dataLength= UART_RX_BUF[dataCount];
				if(dataLength < 3 || dataLength > 8)
				{
					dataLength = 3;
					isGotFrameHeader = false;
				}
			}
			dataCount++;
			if(dataCount == dataLength + 3)
			{
				if(isUartRxCompleted == false)
				{
					isUartRxCompleted = true;
					memcpy(LobotRxBuf, UART_RX_BUF, dataCount+2);
				}
				isGotFrameHeader = false;
			}
		}
	}
	if (TI) {    
		TI = 0;
		busy = 0; 
	}
}

bool isRxCompleted(void)
{
	if(isUartRxCompleted)
	{
		isUartRxCompleted = false;
		return true;
	}
	else
	{
		return false;
	}
}

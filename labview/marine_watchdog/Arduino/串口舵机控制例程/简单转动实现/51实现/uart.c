/******************************************************
 * FileName:      uart.c
 * Company:       深圳乐幻索尔科技
 * Date:           2017/02/18  18:02
 * Description:   串口驱动
 *****************************************************/
#include "uart.h"
#include "LobotSerialServo.h"

#include <string.h>
void uartInit() //波特率115200
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//独立波特率发生器时钟为Fosc,即1T
	BRT = 0xFD;		  //设定独立波特率发生器重装值
	AUXR |= 0x01;		//串口1选择独立波特率发生器为波特率发生器
	AUXR |= 0x10;		//启动独立波特率发生器
	ES = 1;         //使能串口中断
	EA = 1;         //使能全局中断
}


uint8_t busy = 0;   //串口忙标识

/*********************************************************************************
 * Function:    uartWriteByte
 * Description:向串口写入一个字节
 * Parameters:   dat:被写入的数据
 * Return:       无返回
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
 * Description:向串口写入数据
 * Parameters:   buf:被写入的数据的指针,len:被写入的数据的长度
 * Return:       无返回
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
 * Description: 串口中断函数
 * Parameters:   无参数
 * Return:       无返回
 * Others:
 **********************************************************************************/

uint8_t UART_RX_BUF[24]; //串口接收缓存
bool isUartRxCompleted = false; //串口接收完数据帧标识

void receiveHandle(void) interrupt 4
{
	uint8_t rx;  //串口接收字节
	static bool isGotFrameHeader = false; //获得帧头标识  
	static uint8_t frameHeaderCount = 0;  //帧头计数
	static uint8_t dataLength = 3;        //数据长度
	static uint8_t dataCount = 0;         //接收计数，此用作接收缓存数组的下标，所以从0开始
	
	if (RI) {  //接收中断
		RI = 0;  //清楚标识
		rx = SBUF;   //读取接收寄存器
		
		if(!isGotFrameHeader)   //没有获得帧头
		{
			if(rx == 0x55)  //接收数据与帧头相同
			{
				frameHeaderCount++;  //帧头计数加一
				if(frameHeaderCount == 2) //如果连续接收到两个0x55
				{
					frameHeaderCount = 0; //帧头计数清零
					isGotFrameHeader = true; //获得了帧头
					dataCount = 1;  //接收计数为1
				}
			}
			else //接收数据与帧头不相投
			{
				isGotFrameHeader = false; //没有获得帧头
				dataCount = 0;   //计数清零
				frameHeaderCount = 0; //计数清零
			}
		}
		if(isGotFrameHeader) //获得了帧头
		{
			UART_RX_BUF[dataCount] = rx; //将接收到的数据放入接收缓存
			if(dataCount == 3)  //计数等于3的时候，就是数据帧的第四位，此位为不包括帧头及ID号的所有数据长度
			{
				dataLength= UART_RX_BUF[dataCount];  //获取数据长度
				if(dataLength < 3 || dataLength > 8) //判断数据是否过长或者过短，过长及过短都是错误数据
				{
					dataLength = 3;
					isGotFrameHeader = false; //清楚已获得帧头标识，从新开始
				}
			}
			dataCount++;  //接收计数+1
			if(dataCount == dataLength + 3) //如果计数等于 数据长度 + 3 那么就是接受到了完整的数据帧
			{
				if(isUartRxCompleted == false)  
				{
					isUartRxCompleted = true;  //置位接收完成标识
					memcpy(LobotRxBuf, UART_RX_BUF, dataCount+2); //将数据帧复制到 LobotRxBuf，供接收处理函数处理
				}
				isGotFrameHeader = false; //清楚标识，继续接收下一帧
			}
		}
	}
	if (TI) {    //发送完成中断
		TI = 0;  //清楚标识
		busy = 0;  //清楚串口忙标识
	}
}

/*********************************************************************************
 * Function:  receiveHandle
 * Description: 判断是否接收到数据
 * Parameters:   无参数
 * Return:       true为接收到数据，false为没有接收到数据
 * Others:  接收到数据返回true，同时isUartCompleted 标识会被清除
 **********************************************************************************/
 
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

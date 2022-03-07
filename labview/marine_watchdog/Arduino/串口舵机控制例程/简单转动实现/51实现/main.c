/******************************************************
 * FileName:      main.c
 * Company:       深圳乐幻索尔科技
 * Date:          2017/02/18  17:50
 * Description:   LX-16系列串口舵机控制示例
 *****************************************************/
#include "STC12C5A60S2.H"
#include "typedef.h"
#include "intrins.h"
#include "uart.h"
#include "LobotSerialServo.h"

void Delay1000ms()		//@11.0592MHz 延时1000ms
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

#define ID1 1
#define ID2 2

int main()
{
	uartInit(); //初始化 串口 波特率要为 115200
	while(1)
	{
		LobotSerialServoMove(ID1, 100, 500); //ID1号舵机500ms转动到 100位置
		LobotSerialServoMove(ID2, 200, 500); //ID2号舵机500ms转动到 200位置
		Delay1000ms();
		LobotSerialServoMove(ID1, 500, 500); //ID1号舵机500ms转动到 500位置
		LobotSerialServoMove(ID2, 600, 500); //ID2号舵机500ms转动到 600位置
		Delay1000ms();
		LobotSerialServoMove(ID1, 900, 500); //ID1号舵机500ms转动到 900位置
		LobotSerialServoMove(ID2, 1000, 500);//ID2号舵机500ms转动到 1000位置
		Delay1000ms();
		LobotSerialServoMove(ID1, 500, 500); //ID1号舵机500ms转动到 500位置
		LobotSerialServoMove(ID2, 600, 500); //ID2号舵机500ms转动到 600位置
		Delay1000ms();
	}
}

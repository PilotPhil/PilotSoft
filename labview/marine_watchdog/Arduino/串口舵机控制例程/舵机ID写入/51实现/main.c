/******************************************************
 * FileName:      main.c
 * Company:       ????
 * Date:          2016/07/09  09:30
 * Description:   Lobot???????????,??stc89c52rc??
 *                @@????:????????????9600???@@
 *****************************************************/
#include "STC12C5A60S2.H"
#include "typedef.h"
#include "intrins.h"
#include "uart.h"
#include "LobotSerialServo.h"

void Delay1000ms()		//@11.0592MHz
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


int main()
{
	uartInit();
	while(1)
	{
		LobotSerialServoSetID(254, 1);
		Delay1000ms();
	}
}

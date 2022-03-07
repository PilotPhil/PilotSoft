#include "delay.h"
#include "uart.h"
#include "LobotSerialServo.h"
#include "bool.h"

 int main(void)
 {	
 	SystemInit();   //系统时钟等初始化
	delay_init(72);	//延时初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uartInit(115200);//串口初始化为115200

	while(1)
	{
		LobotSerialServoSetID(254, 1);
		delay_ms(1000);
	}
}

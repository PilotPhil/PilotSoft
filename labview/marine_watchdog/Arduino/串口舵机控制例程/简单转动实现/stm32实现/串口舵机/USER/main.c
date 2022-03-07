#include "delay.h"
#include "uart.h"
#include "LobotSerialServo.h"
#include "bool.h"

#define ID1 1
#define ID2 2

 int main(void)
 {	
 	SystemInit();   //系统时钟等初始化
	delay_init(72);	//延时初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uartInit(115200);//串口初始化为115200

	while(1)
	{
			LobotSerialServoMove(ID1, 100, 500);  //舵机1用500ms转动到100位置
			LobotSerialServoMove(ID2, 300, 500);  //舵机2用500ms转动到300位置
			delay_ms(1000);
			LobotSerialServoMove(ID1, 500, 500);  //舵机1用500ms转动到500位置
			LobotSerialServoMove(ID2, 600, 500);  //舵机2用500ms转动到600位置
			delay_ms(1000);
			LobotSerialServoMove(ID1, 900, 800);  //舵机1用800ms转动到900位置
			LobotSerialServoMove(ID2, 700, 800);  //舵机2用800ms转动到700位置
			delay_ms(1000);
			LobotSerialServoMove(ID1, 500, 500);  //舵机1用800ms转动到700位置
			LobotSerialServoMove(ID2, 600, 500);  //舵机2用800ms转动到700位置
			delay_ms(1000);
	}
}

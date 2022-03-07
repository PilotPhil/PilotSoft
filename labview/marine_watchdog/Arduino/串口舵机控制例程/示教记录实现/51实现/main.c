/******************************************************
 * FileName:      main.c
 * Company:       深圳乐幻索尔科技
 * Date:          2017/02/20  10:24
 * Description:  
 *****************************************************/
#include "STC12C5A60S2.H"
#include "typedef.h"
#include "intrins.h"
#include "uart.h"
#include "LobotSerialServo.h"

void Delay1000ms()		//@11.0592MHz  延时1000ms
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

void Delay500ms()		//@11.0592MHz  延时500ms
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay10ms()		//@11.0592MHz   延时10ms
{
	unsigned char i, j;

	i = 108;
	j = 145;
	do
	{
		while (--j);
	} while (--i);
}


sbit Key1 = P3^2;  //按钮1  //模式切换
sbit Key2 = P3^3;  //按钮2  //运行模式下，运行动作， 录制模式下，记录动作

#define ID1 1
#define ID2 2

int main()
{
	bool run = false;
	char step = 0;
	char mode = 0;

	uint16_t pos[4] = {100,200,300,400};
	uint16_t pos1[4] = {100,200,300,400};

	Key1 = 1;
	Key2 = 1;

	uartInit();
	LobotSerialServoMove(ID1, 500, 100);
	LobotSerialServoMove(ID2, 500, 100);

  while (1) {
    if (mode == 0)
    {
      if (run)   //如果run标识为true，就运行
      {
        LobotSerialServoMove(ID1, pos[step], 500);     //运动到记录的位置
				LobotSerialServoMove(ID2, pos1[step++], 500);
        if (step == 4)
        {
          step = 0;
          run = false;
        }
        Delay1000ms();
      }
      if (!Key2)    //按下按键2，将run置为true
      {
        Delay10ms();   
        if (!Key2)
        {
          run = true;
          step = 0;
          Delay500ms();
        }
      }
      if (!Key1)    //按下按键1 卸载舵机的力矩，转移到模式1 ，即记录模式
      {
        Delay10ms();
        if (!Key1)
        {
          LobotSerialServoUnload(ID1);   //卸载舵机1
					LobotSerialServoUnload(ID2);   //卸载舵机2
          mode = 1;
          step = 0;
          Delay500ms();
        }
      }
    }
    if (mode == 1)
    {
      if (!Key2)   //按下按键2，读取舵机当前位置，并记录下来
      {
        Delay10ms();
        if (!Key2)
        {
          pos[step] = LobotSerialServoReadPosition(ID1);
					pos1[step++] = LobotSerialServoReadPosition(ID2);
          if (step == 4)
            step = 0;
          Delay500ms();
        }
      }
      if (!Key1)   //如果按下按键1，加载舵机力矩，转移到模式0
      {
        Delay10ms();
        if (!Key1)
        {
          LobotSerialServoMove(ID1, LobotSerialServoReadPosition(ID1), 200);
					LobotSerialServoMove(ID2, LobotSerialServoReadPosition(ID2), 200);
          mode = 0;
          Delay500ms();
        }
      }
    }
  }
}

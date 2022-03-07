/*******************************************************************************
* 文件名: LobotSerial.c
* 作者: 深圳市乐幻索尔科技
* 日期:20170217
* LX串口Demo
*******************************************************************************/
#include "uart.h"
#include "LobotSerialServo.h"
#include <stdarg.h>
#include <string.h>


#define LobotSerialWrite  uartWriteBuf /*修改uartWriteBuf为你自己的串口发送函数,名字可以自定义，但函数原型需与下相同*/
                                       /*uartWriteBuf(uint8_t *buf, uint8_t len); 函数原型*/

#define GET_LOW_BYTE(A) ((uint8_t)(A))
//获取A的低八位
#define GET_HIGH_BYTE(A) ((uint8_t)((A) >> 8))
//获取A的高八位
#define BYTE_TO_HW(A, B) ((((uint16_t)(A)) << 8) | (uint8_t)(B))
//将高地八位合成为十六位

uint8_t LobotRxBuf[24];

//校验计算
uint8_t LobotCheckSum(uint8_t buf[])
{
  uint8_t i;
  uint16_t temp = 0;
  for (i = 2; i < buf[3] + 2; i++) 
	{
    temp += buf[i];
  }
  temp = ~temp;
  i = (uint8_t)temp;
  return i;
}

//写入舵机的ID
void LobotSerialServoSetID(uint8_t oldID, uint8_t newID)
{
	uint8_t buf[7];
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = oldID;
  buf[3] = 4;
  buf[4] = LOBOT_SERVO_ID_WRITE;
  buf[5] = newID;
  buf[6] = LobotCheckSum(buf);
	
  LobotSerialWrite(buf, 7);
}

//让舵机在指定时间转到指定位置
void LobotSerialServoMove(uint8_t id, int16_t position, uint16_t time)
{
  uint8_t buf[10];
  if(position < 0)
	position = 0;
  if(position > 1000)
    position = 1000;
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 7;
  buf[4] = LOBOT_SERVO_MOVE_TIME_WRITE;
  buf[5] = GET_LOW_BYTE(position);
  buf[6] = GET_HIGH_BYTE(position);
  buf[7] = GET_LOW_BYTE(time);
  buf[8] = GET_HIGH_BYTE(time);
  buf[9] = LobotCheckSum(buf);
	
  LobotSerialWrite(buf, 10);
}

//卸载力矩
void LobotSerialServoUnload(uint8_t id)
{
  uint8_t buf[7];
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 4;
  buf[4] = LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE;
  buf[5] = 0;
  buf[6] = LobotCheckSum(buf);
	
  LobotSerialWrite(buf, 7);
}
//加载力矩
void LobotSerialServoLoad(uint8_t id)
{
  uint8_t buf[7];
  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 4;
  buf[4] = LOBOT_SERVO_LOAD_OR_UNLOAD_WRITE;
  buf[5] = 1;
  buf[6] = LobotCheckSum(buf);
	
  LobotSerialWrite(buf, 7);
}
//获得舵机当前位置
int LobotSerialServoReadPosition(uint8_t id)
{
  int ret;
  uint8_t buf[6];

  buf[0] = buf[1] = LOBOT_SERVO_FRAME_HEADER;
  buf[2] = id;
  buf[3] = 3;
  buf[4] = LOBOT_SERVO_POS_READ;
  buf[5] = LobotCheckSum(buf);
	
	LobotSerialWrite(buf, 6);  //发送获取位置的命令
	ret = LobotSerialMsgHandle(); //获取接收到的数据
	
  return ret; //返回舵机的位置
}

int LobotSerialMsgHandle(void)
{
	uint8_t cmd;
	int count = 10000;
	int16_t ret;
	
	while(!isRxCompleted()) //检查是否接收到数据，没有的话一直等待，知道count小于0，返回 -1
	{
		count--;
		if(count < 0)
			return -1;
	}
	
	if(LobotCheckSum(LobotRxBuf) != LobotRxBuf[LobotRxBuf[3]+2])
	{
		return -2;  //进行校验，校验不过则返回-2
	}
	cmd = LobotRxBuf[4];
	switch(cmd)
	{
		case LOBOT_SERVO_POS_READ:
			ret = (int16_t)BYTE_TO_HW(LobotRxBuf[6], LobotRxBuf[5]); //合成16位数据
			return ret; //返回数据
		default:
			break;
	}
	return 0;
}

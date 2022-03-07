#include "delay.h"
#include "uart.h"
#include "LobotSerialServo.h"
#include "bool.h"

#define ID1 1
#define ID2 2

void keyInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

 int main(void)
 {
	bool run = false;
	char step = 0;
	char mode = 0;
	int pos[4] = {100, 200, 300, 400};
	int pos1[4] = {100, 200, 300, 400};
	
 	SystemInit();   //ÏµÍ³Ê±ÖÓµÈ³õÊ¼»¯
	delay_init(72);	//ÑÓÊ±³õÊ¼»¯
	keyInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ÉèÖÃNVICÖĞ¶Ï·Ö×é2:2Î»ÇÀÕ¼ÓÅÏÈ¼¶£¬2Î»ÏìÓ¦ÓÅÏÈ¼¶
	uartInit(115200);//´®¿Ú³õÊ¼»¯Îª115200

	while(1){
		//modeµÈÓÚ0£¬ÔËĞĞÄ£Ê½£¬°´ÏÂ°´Å¥2£¬ÔËĞĞ¼ÇÂ¼µÄ¶¯×÷£¬°´ÏÂ°´Å¥1ÇĞ»»ÎªÂ¼ÖÆÄ£Ê½¡
		if(mode == 0)
		{
			if(run)
			{
				LobotSerialServoMove(ID1, pos[step], 500);
				LobotSerialServoMove(ID2, pos1[step++], 500);
				if(step == 4)
				{
					step = 0;
					run = false;
				}
				delay_ms(1000);
			}
			if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) //°´Å¥2 °´ÏÂ
			{
				delay_ms(10);        //¼òµ¥Ïû¶¶
				if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) 
				{
					run = true; //ÔËĞĞ
					step = 0;
					delay_ms(500);
				}
			}
			if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)) //°´Å¥1°´ÏÂ
			{
				delay_ms(10);  //¼òµ¥Ïû¶¶
				if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8))
				{
					LobotSerialServoUnload(ID1); //¶æ»úĞ¶ÔØÁ¦¾Ø£¬±äÎª¿ÉÒÔÅ¤¶¯
					LobotSerialServoUnload(ID2); 
					mode = 1;
					step = 0;
					delay_ms(500);
				}
			}
		}
		//modeµÈÓÚ1£¬ Â¼ÖÆÄ£Ê½£¬ °´ÏÂ°´Å¥2£¬¼ÇÂ¼ÏÂµ±Ç°Î»ÖÃ£¬°´ÏÂ°´Å¥1ÇĞ»»»ØÔËĞĞÄ£Ê½
		if(mode == 1)
		{
			if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9)) //°´Å¥2 ±»°´ÏÂ
			{
				delay_ms(10);  //¼òµ¥Ïû¶¶
				if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))
				{
					pos[step] = LobotSerialServoReadPosition(ID1); //¶ÁÈ¡¶æ»úµ±Ç°Î»ÖÃ£¬¼ÇÂ¼ÏÂÀ´
					pos1[step++] = LobotSerialServoReadPosition(ID2);
					if(step == 4)
						step = 0;
					delay_ms(500);
				}
			}
			if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8)) //°´Å¥1 ±»°´ÏÂ
			{
				delay_ms(10); //¼òµ¥Ïû¶¶
				if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8))
				{
					LobotSerialServoMove(ID1,LobotSerialServoReadPosition(ID1),200); //¶ÁÈ¡µ±Ç°Î»ÖÃ£¬ÔË¶¯µ½µ±Ç°Î»ÖÃ£¬ÊµÏÖ¼ÓÔØÁ¦¾Ø
					LobotSerialServoMove(ID2,LobotSerialServoReadPosition(ID2),200);
					//Ö±½ÓÊ¹ÓÃ¼ÓÔØÁ¦¾ØµÄÃüÁî£¬»áÖ±½ÓÔË¶¯µ½Ğ¶ÔØÁ¦¾ØÇ°µÄ×îºóÎ»ÖÃ£¬²»»á±£³ÖÔÚµ±Ç°Î»ÖÃ¡£
					mode = 0;
					delay_ms(500);
				}
			}
		}
	}
}

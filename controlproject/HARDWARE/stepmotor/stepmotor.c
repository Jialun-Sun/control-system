#include "stm32f10x.h"   
#include "stepmotor.h"
#include "delay.h"
uint8_t STEP;
void STEP_MOTOR_Init(void)
{
	RCC_APB2PeriphClockCmd(STEP_MOTOR_CLK, ENABLE);			//开启GPIOA的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = STEP_MOTOR_A | STEP_MOTOR_B | STEP_MOTOR_C | STEP_MOTOR_D;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);							//将PA6和PA7引脚初始化为上拉输入
	
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B | STEP_MOTOR_C | STEP_MOTOR_D);//各接口置0
}

void STEP_MOTOR_OFF (void)  //电机断电 全拉低
{
	GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B | STEP_MOTOR_C | STEP_MOTOR_D);//各接口置0
}

void STEP_MOTOR_ON (u8 a,u16 speed)  //电机单步8拍
{
	switch (a){
		case 0:
		GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_B | STEP_MOTOR_C | STEP_MOTOR_D);//0
		GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_A);//1
		delay_ms(speed);

			break;
		case 1:
		GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_C | STEP_MOTOR_D);//0
		GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B);//1
		delay_ms(speed);
			break;
		case 2:
		GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_C | STEP_MOTOR_D);//0
		GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_B);//1
		delay_ms(speed);
			break;
		case 3:
		GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_D);//0
		GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_B | STEP_MOTOR_C);//1
		delay_ms(speed);
			break;
		case 4:
		GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B | STEP_MOTOR_D);//0
		GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_C);//1
		delay_ms(speed);
			break;
		case 5:
		GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B);//0
		GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_C | STEP_MOTOR_D);//1
		delay_ms(speed);
			break;
		case 6:
		GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_B | STEP_MOTOR_C);//0
		GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_D);//1
		delay_ms(speed);
			break;
		case 7:
		GPIO_ResetBits(STEP_MOTOR_PORT,STEP_MOTOR_B | STEP_MOTOR_C);//0
		GPIO_SetBits(STEP_MOTOR_PORT,STEP_MOTOR_A | STEP_MOTOR_D);//1
		delay_ms(speed);
			break;
		default:
			break;
	}
	delay_ms(speed); //延时
	//STEP_MOTOR_OFF();//进入断电状态，防电机过热
}


void STEP_MOTOR_NUM (u8 RL,u16 num,u8 speed)  //电机按步数运行
{
	u16 i;
	for(i=0;i<num;i++)
    {	
		if(RL==1){ //当RL=1右转，RL=0左转
			STEP++;
			if(STEP>7)STEP=0;
		}else{
			if(STEP==0)STEP=8;
			STEP--;
		}
		STEP_MOTOR_ON(STEP,speed);
	}
}
 
void STEP_MOTOR_LOOP (u8 RL,u8 LOOP,u8 speed)  //电机按角度运行
{
	STEP_MOTOR_NUM(RL,LOOP*32,speed); //这里CSDN说步进电机有点老给的4076，原理上是360*32/4096度/loop，即2.8125/loop，21.33333个loop
}

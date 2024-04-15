#include "stm32f10x.h"   
#include "exti.h"   
#include "led.h"
#include "motor.h"
uint8_t Mspeed=0;
void EXTIInit (void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//EXTI和NVIC的外设时钟是一直打开的，不需要手动开启
	//RCC管的都是内核之外的时钟，NVIC是在内核里的，和CPU共用一个时钟
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//配置GPIO↑
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	//配置GPIO↑选择b，然后选择EXTI的14号线
	//配置EXTI↓
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line14;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	
	EXTI_Init(&EXTI_InitStruct);
	//配置NVIC
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2 //已经在主函数配置完成
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//TIM2在NVIC的通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line14) == SET)
	{
	LED1=!LED1;
		
//		if(Mspeed==0)
//		{
//			Mspeed=30;
//			motor_Speed(Mspeed);
//		}
//		else if(Mspeed==30)
//		{
//			Mspeed=60;
//			motor_Speed(Mspeed);
//		}
//		else if(Mspeed==60)
//		{
//			Mspeed=90;
//			motor_Speed(Mspeed);
//		}
//		else
//		{
//			Mspeed=0;
//			motor_Speed(Mspeed);
//		}
	EXTI_ClearITPendingBit(EXTI_Line14);
	}
	
	
}





//这里EXTI线所有的15-10都是用一个中断向量来处理
//也就是说15-10共用一个中断向量函数，那么我们需要用if语句判断到底是哪个发生了中断
//下面的示例来讲述如何用
//void EXTI15_10_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line10) != RESET)
//	{
//		delay ms(10);//消抖if(KEY2 == 0){LED1=!LED1;
//		while(!KEY2);
//		EXTI_ClearITPendingBit(EXTI_Line10); //清除中断标志位}
//	}
//	if(EXTI_GetITStatus(EXTI_Line14)!= RESET)
//	{
//		delay ms(10);//消抖if(KEY3 == 0){LED2=!LED2;
//		while(!KEY3);
//		EXTI_ClearITPendingBit(EXTI_Line14);
//	}
//}



































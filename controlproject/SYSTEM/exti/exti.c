#include "stm32f10x.h"   
#include "exti.h"   
#include "led.h"
#include "motor.h"
uint8_t Mspeed=0;
void EXTIInit (void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//EXTI��NVIC������ʱ����һֱ�򿪵ģ�����Ҫ�ֶ�����
	//RCC�ܵĶ����ں�֮���ʱ�ӣ�NVIC�����ں���ģ���CPU����һ��ʱ��
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//����GPIO��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	//����GPIO��ѡ��b��Ȼ��ѡ��EXTI��14����
	//����EXTI��
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line14;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	
	EXTI_Init(&EXTI_InitStruct);
	//����NVIC
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2 //�Ѿ����������������
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//TIM2��NVIC��ͨ��
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





//����EXTI�����е�15-10������һ���ж�����������
//Ҳ����˵15-10����һ���ж�������������ô������Ҫ��if����жϵ������ĸ��������ж�
//�����ʾ�������������
//void EXTI15_10_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line10) != RESET)
//	{
//		delay ms(10);//����if(KEY2 == 0){LED1=!LED1;
//		while(!KEY2);
//		EXTI_ClearITPendingBit(EXTI_Line10); //����жϱ�־λ}
//	}
//	if(EXTI_GetITStatus(EXTI_Line14)!= RESET)
//	{
//		delay ms(10);//����if(KEY3 == 0){LED2=!LED2;
//		while(!KEY3);
//		EXTI_ClearITPendingBit(EXTI_Line14);
//	}
//}



































#include "stm32f10x.h"   
#include "motor.h"   


void Motor12_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//����TIM2
	

	//����GPIO���
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	
	
	
	
	//����ʱ����Ԫ
	TIM_InternalClockConfig(TIM1);//TIM1��ʱ����Ԫ���ڲ�ʱ������

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ָ��ʱ�ӷ�Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100-1;//ARR���Զ���װ�Ĵ���
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720-1;//Ԥ��ƵPSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM1,TIM_FLAG_Update);//װ��PSCʱ��������baseinit����������������¼��������жϣ�������init֮���ֱ�ӽ����ж�
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 50;//CCR��ֵ
	
	TIM_OC1Init(TIM1,&TIM_OCInitStruct);
	TIM_OC2Init(TIM1,&TIM_OCInitStruct);
	
	//������ʱ��
	TIM_Cmd(TIM1, ENABLE);
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure1;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_7;
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure1);	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

}


void Motor34_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//����TIM2
	

	//����GPIO���
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	
	
	
	
	//����ʱ����Ԫ
	TIM_InternalClockConfig(TIM4);//TIM1��ʱ����Ԫ���ڲ�ʱ������

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ָ��ʱ�ӷ�Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100-1;//ARR���Զ���װ�Ĵ���
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720-1;//Ԥ��ƵPSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);//װ��PSCʱ��������baseinit����������������¼��������жϣ�������init֮���ֱ�ӽ����ж�
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 50;//CCR��ֵ
	
	TIM_OC1Init(TIM4,&TIM_OCInitStruct);
	TIM_OC2Init(TIM4,&TIM_OCInitStruct);
	
	//������ʱ��
	TIM_Cmd(TIM4, ENABLE);
	

	RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure1;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_3 |GPIO_Pin_4;
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure1);	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

}




void PWM_SetCompareMotor1(uint16_t Compare)
{

	TIM_SetCompare1(TIM1,Compare);


}
void PWM_SetCompareMotor2(uint16_t Compare)
{


	TIM_SetCompare2(TIM1,Compare);

}
void PWM_SetCompareMotor3(uint16_t Compare)
{

	TIM_SetCompare1(TIM4,Compare);

}
void PWM_SetCompareMotor4(uint16_t Compare)
{


	TIM_SetCompare2(TIM4,Compare);
}



















void motor1_Speed(uint8_t Speed)
{
	if(Speed > 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		PWM_SetCompareMotor1(Speed);
	}
	else
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		PWM_SetCompareMotor1(-Speed);
	}
}

void motor2_Speed(uint8_t Speed)
{
	if(Speed > 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_6);
		GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		PWM_SetCompareMotor2(Speed);
	}
	else
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_7);
		GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		PWM_SetCompareMotor2(-Speed);
	}
}

void motor3_Speed(uint8_t Speed)
{
	if(Speed > 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_10);
		GPIO_ResetBits(GPIOA, GPIO_Pin_11);
		PWM_SetCompareMotor3(Speed);
	}
	else
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_11);
		GPIO_ResetBits(GPIOA, GPIO_Pin_10);
		PWM_SetCompareMotor3(-Speed);
	}
}

void motor4_Speed(uint8_t Speed)
{
	if(Speed > 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
		GPIO_ResetBits(GPIOA, GPIO_Pin_9);
		PWM_SetCompareMotor4(Speed);
	}
	else
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_9);
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		PWM_SetCompareMotor4(-Speed);
	}
}

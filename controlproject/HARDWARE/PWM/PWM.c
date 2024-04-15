#include "stm32f10x.h"   
#include "PWM.h"   

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//����TIM3
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//��ӳ��AFIO����֮һ
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	
	
	
	
	//����ʱ����Ԫ
	TIM_InternalClockConfig(TIM3);//TIM3��ʱ����Ԫ���ڲ�ʱ������

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ָ��ʱ�ӷ�Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100-1;//ARR���Զ���װ�Ĵ���
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36-1;//Ԥ��ƵPSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);//װ��PSCʱ��������baseinit����������������¼��������жϣ�������init֮���ֱ�ӽ����ж�
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 70;//CCR��ֵ
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);
	
	//������ʱ��
	TIM_Cmd(TIM3, ENABLE);
	
	
}

void PWM_SetCompare(uint16_t Compare)
{

	TIM_SetCompare2(TIM3,Compare);

}


#include "stm32f10x.h"                  // Device header
#include "led.h" 
#include "Timer.h"	
#include "Encoder.h"	
uint8_t counter1;
int16_t Speed;
void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//����TIM2
	
	//����ʱ����Ԫ
	TIM_InternalClockConfig(TIM4);//TIM2��ʱ����Ԫ���ڲ�ʱ������

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ָ��ʱ�ӷ�Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10000-1;//ARR���Զ���װ�Ĵ���
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200-1;//Ԥ��ƵPSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);//װ��PSCʱ��������baseinit����������������¼��������жϣ�������init֮���ֱ�ӽ����ж�
	//��ô���������־λ�����Ա�������ϵ�ֱ���ж�
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);//UPDATE,�����жϣ���������������ж�
	
	
	
	//��ͨTIM2��NVIC��ͨ��
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�Ѿ����������������
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;//TIM2��NVIC��ͨ��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	//������ʱ��
	TIM_Cmd(TIM4, ENABLE);
	
}

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update)==SET)
	{
	
	
	LED1=!LED1;
	counter1 ++;
	Speed = Encoder_Get();								//ÿ���̶�ʱ��ζ�ȡһ�α�������������ֵ����Ϊ�ٶ�ֵ
		
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}




}


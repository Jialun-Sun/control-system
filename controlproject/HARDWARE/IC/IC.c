#include "stm32f10x.h"   
#include "IC.h"   

void IC_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//����TIM3
	
	

	//��GPIO����Ϊ����ģʽ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	
	
	
	
	//����ʱ����Ԫ
	TIM_InternalClockConfig(TIM2);//TIM3��ʱ����Ԫ���ڲ�ʱ������

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//ָ��ʱ�ӷ�Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;//ARR���Զ���װ�Ĵ���
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1;//Ԥ��ƵPSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//װ��PSCʱ��������baseinit����������������¼��������жϣ�������init֮���ֱ�ӽ����ж�
	
	//�������벶��Ԫ �˲���������ѡ��ͱ��ؼ�⣬�������뻹��ֱ������Ƶ���
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter = 0x1;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM2, &TIM_ICInitStruct);
	
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStruct.TIM_ICFilter = 0x1;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Falling;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_IndirectTI;
	TIM_ICInit(TIM2, &TIM_ICInitStruct);
	//TIM_PWMIConfig(TIM2, &TIM_ICInitStruct);						//���ṹ���������TIM_PWMIConfig������TIM3�����벶��ͨ��
//																	//�˺���ͬʱ�����һ��ͨ������Ϊ�෴�����ã�ʵ��PWMIģʽ
	/* 
	TIM_PWMIConfig(TIM2, &TIM_ICInitStruct);��������൱���Զ�����TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
																TIM_ICInitStruct.TIM_ICFilter = 0xF;
																TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Falling;
																TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
																TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_IndirectTI;
																TIM_ICInit(TIM2, &TIM_ICInitStruct);
	����ת���ṹ�嶨�忴
	Ȼ����һ�������Ĳ����ǣ�TIM_ICInitTypeDef TIM_ICInitStruct;ֻ����ʹ��һ�Σ���Ȼʹ������Ҳ���ᱨ�����ǻ��޷�����ִ��IC�ĳ���
	�൱��һ���ṹ��Ķ��壬����ͬʱ����������������
	
	
	
	
	
	
	
	*/
	//���ô�ģʽ����
	TIM_SelectInputTrigger(TIM2,TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM2,TIM_SlaveMode_Reset);
	//������ʱ��
	TIM_Cmd(TIM2, ENABLE);
	
	
}

uint32_t IC_GetFreq(void)
{
	return 1000000 / (TIM_GetCapture1(TIM2) + 1);		//���ܷ��õ�Ƶ��fx = fc / N�����ﲻִ��+1�Ĳ���Ҳ��
}
uint32_t IC_GetDuty(void)
{
	return (TIM_GetCapture2(TIM2) + 1) * 100 / (TIM_GetCapture1(TIM2) + 1);	//ռ�ձ�Duty = CCR2 / CCR1 * 100�����ﲻִ��+1�Ĳ���Ҳ��
}

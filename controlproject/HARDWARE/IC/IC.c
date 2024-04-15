#include "stm32f10x.h"   
#include "IC.h"   

void IC_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//开启TIM3
	
	

	//打开GPIO，变为输入模式
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	
	
	
	
	//配置时基单元
	TIM_InternalClockConfig(TIM2);//TIM3的时基单元由内部时钟驱动

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//指定时钟分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;//ARR，自动重装寄存器
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1;//预分频PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//装载PSC时会让上面baseinit这个函数产生更新事件（更新中断），所以init之后会直接进入中断
	
	//配置输入捕获单元 滤波器，极性选择和边沿检测，交叉输入还是直连，分频与否
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
	//TIM_PWMIConfig(TIM2, &TIM_ICInitStruct);						//将结构体变量交给TIM_PWMIConfig，配置TIM3的输入捕获通道
//																	//此函数同时会把另一个通道配置为相反的配置，实现PWMI模式
	/* 
	TIM_PWMIConfig(TIM2, &TIM_ICInitStruct);这个函数相当于自动配置TIM_ICInitStruct.TIM_Channel = TIM_Channel_2;
																TIM_ICInitStruct.TIM_ICFilter = 0xF;
																TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Falling;
																TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
																TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_IndirectTI;
																TIM_ICInit(TIM2, &TIM_ICInitStruct);
	可以转到结构体定义看
	然后还有一点很神奇的操作是，TIM_ICInitTypeDef TIM_ICInitStruct;只允许使用一次，当然使用两次也不会报错，但是会无法正常执行IC的程序
	相当于一个结构体的定义，可以同时定义其中两个配置
	
	
	
	
	
	
	
	*/
	//配置从模式触发
	TIM_SelectInputTrigger(TIM2,TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM2,TIM_SlaveMode_Reset);
	//启动定时器
	TIM_Cmd(TIM2, ENABLE);
	
	
}

uint32_t IC_GetFreq(void)
{
	return 1000000 / (TIM_GetCapture1(TIM2) + 1);		//测周法得到频率fx = fc / N，这里不执行+1的操作也可
}
uint32_t IC_GetDuty(void)
{
	return (TIM_GetCapture2(TIM2) + 1) * 100 / (TIM_GetCapture1(TIM2) + 1);	//占空比Duty = CCR2 / CCR1 * 100，这里不执行+1的操作也可
}

#include "stm32f10x.h"                  // Device header
#include "led.h" 
#include "Timer.h"	
#include "Encoder.h"	
uint8_t counter1;
int16_t Speed;
void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//开启TIM2
	
	//配置时基单元
	TIM_InternalClockConfig(TIM4);//TIM2的时基单元由内部时钟驱动

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//指定时钟分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 10000-1;//ARR，自动重装寄存器
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200-1;//预分频PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);//装载PSC时会让上面baseinit这个函数产生更新事件（更新中断），所以init之后会直接进入中断
	//那么这里清除标志位，可以避免进入上电直接中断
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);//UPDATE,更新中断，计数器溢出产生中断
	
	
	
	//打通TIM2到NVIC的通道
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//已经在主函数配置完成
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;//TIM2在NVIC的通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	//启动定时器
	TIM_Cmd(TIM4, ENABLE);
	
}

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update)==SET)
	{
	
	
	LED1=!LED1;
	counter1 ++;
	Speed = Encoder_Get();								//每隔固定时间段读取一次编码器计数增量值，即为速度值
		
	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}




}


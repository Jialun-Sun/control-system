#ifndef __stepmotor_H
#define __stepmotor_H	 
#include "stm32f10x.h" 
#include "delay.h"
extern  uint8_t STEP;

#define STEP_MOTOR_PORT		GPIOF	//定义IO接口所在组
#define STEP_MOTOR_A		GPIO_Pin_1	//定义IO接口
#define STEP_MOTOR_B		GPIO_Pin_2	//定义IO接口
#define STEP_MOTOR_C		GPIO_Pin_3	//定义IO接口
#define STEP_MOTOR_D		GPIO_Pin_4	//定义IO接口

#define STEP_MOTOR_CLK      RCC_APB2Periph_GPIOF

void STEP_MOTOR_Init(void);

void STEP_MOTOR_OFF (void);
void STEP_MOTOR_ON (u8 a,u16 speed);

void STEP_MOTOR_NUM (u8 RL,u16 num,u8 speed);
void STEP_MOTOR_LOOP (u8 RL,u8 LOOP,u8 speed);



#endif


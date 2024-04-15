#ifndef __motor_H
#define __motor_H	 
#include "stm32f10x.h" 


void Motor12_Init(void);
void Motor34_Init(void);

void PWM_SetCompareMotor1(uint16_t Compare);
void PWM_SetCompareMotor2(uint16_t Compare);
void PWM_SetCompareMotor3(uint16_t Compare);
void PWM_SetCompareMotor4(uint16_t Compare);


void motor1_Speed(uint8_t Speed);
void motor2_Speed(uint8_t Speed);
void motor3_Speed(uint8_t Speed);
void motor4_Speed(uint8_t Speed);
#endif

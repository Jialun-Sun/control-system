#include "stm32f10x.h"  
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "ADC.h"
uint16_t temp;
uint16_t press;
float temper;
float temperature;

int main(void)
{	
	
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 	//串口初始化为115200
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置中断优先级分组,整个程序只能分配一次
 	LED_Init();//LED端口初始化
	LCD_Init();
	KEY_Init();
	POINT_COLOR=RED;
    LCD_Clear(WHITE);
	temp_Init();
	OPT101_Init();
  	while(1) 
	{
		POINT_COLOR=RED;	
		LCD_ShowString(50,40,210,24,24,"Final Project"); 
		LCD_ShowString(90,70,200,16,16,"2024/3/30");
		temp = AD_GetValue();
		temper = (temp * 3.3)/4095;
		temperature = ((1.43 - temper)/0.0043+25) - 8;
		LCD_ShowString(10,100,200,16,16,"temperature:");
		LCD_ShowxNum(110,100,temperature,4,16,0x00);
		LCD_ShowString(150,100,200,16,16,"Centigrade");
		
		
		press = AD2_GetValue();
		
		LCD_ShowString(10,130,200,16,16,"pressure:");
		LCD_ShowxNum(110,130,press,4,16,0x00);
		LCD_ShowString(150,130,200,16,16,"psi");
	}

} 




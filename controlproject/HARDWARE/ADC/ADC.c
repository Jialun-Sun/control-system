#include "stm32f10x.h"
#include "ADC.h"

void pres_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//��PA0���ų�ʼ��Ϊģ������
	
	ADC_RegularChannelConfig(ADC2, ADC_Channel_9, 1, ADC_SampleTime_55Cycles5);
	ADC_DeInit(ADC2); 
	ADC_InitTypeDef ADC_InitStructure;						//����ṹ�����
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		//ģʽ��ѡ�����ģʽ��������ʹ��ADC1
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//���ݶ��룬ѡ���Ҷ���
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//�ⲿ������ʹ���������������Ҫ�ⲿ����
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;		//����ת����ʧ�ܣ�ÿת��һ�ι��������к�ֹͣ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;			//ɨ��ģʽ��ʧ�ܣ�ֻת�������������1��һ��λ��
	ADC_InitStructure.ADC_NbrOfChannel = 1;					//ͨ������Ϊ1������ɨ��ģʽ�£�����Ҫָ������1�������ڷ�ɨ��ģʽ�£�ֻ����1
	ADC_Init(ADC2, &ADC_InitStructure);	
	
	ADC_Cmd(ADC2, ENABLE);
	/*ADCУ׼*/
	ADC_ResetCalibration(ADC2);								//�̶����̣��ڲ��е�·���Զ�ִ��У׼
	while (ADC_GetResetCalibrationStatus(ADC2) == SET);
	ADC_StartCalibration(ADC2);
	while (ADC_GetCalibrationStatus(ADC2) == SET);
}


void OPT101_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//��PA0���ų�ʼ��Ϊģ������
	
	ADC_RegularChannelConfig(ADC2, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
	
	ADC_InitTypeDef ADC_InitStructure;						//����ṹ�����
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		//ģʽ��ѡ�����ģʽ��������ʹ��ADC1
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//���ݶ��룬ѡ���Ҷ���
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//�ⲿ������ʹ���������������Ҫ�ⲿ����
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;		//����ת����ʧ�ܣ�ÿת��һ�ι��������к�ֹͣ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;			//ɨ��ģʽ��ʧ�ܣ�ֻת�������������1��һ��λ��
	ADC_InitStructure.ADC_NbrOfChannel = 1;					//ͨ������Ϊ1������ɨ��ģʽ�£�����Ҫָ������1�������ڷ�ɨ��ģʽ�£�ֻ����1
	ADC_Init(ADC2, &ADC_InitStructure);	
	
	ADC_Cmd(ADC2, ENABLE);
	/*ADCУ׼*/
	ADC_ResetCalibration(ADC2);								//�̶����̣��ڲ��е�·���Զ�ִ��У׼
	while (ADC_GetResetCalibrationStatus(ADC2) == SET);
	ADC_StartCalibration(ADC2);
	while (ADC_GetCalibrationStatus(ADC2) == SET);
}

void temp_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_239Cycles5);
	
	ADC_InitTypeDef ADC_InitStructure;						//����ṹ�����
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		//ģʽ��ѡ�����ģʽ��������ʹ��ADC1
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//���ݶ��룬ѡ���Ҷ���
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//�ⲿ������ʹ���������������Ҫ�ⲿ����
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;		//����ת����ʧ�ܣ�ÿת��һ�ι��������к�ֹͣ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;			//ɨ��ģʽ��ʧ�ܣ�ֻת�������������1��һ��λ��
	ADC_InitStructure.ADC_NbrOfChannel = 1;					//ͨ������Ϊ1������ɨ��ģʽ�£�����Ҫָ������1�������ڷ�ɨ��ģʽ�£�ֻ����1
	ADC_Init(ADC1, &ADC_InitStructure);	
	ADC_TempSensorVrefintCmd(ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	/*ADCУ׼*/
	ADC_ResetCalibration(ADC1);								//�̶����̣��ڲ��е�·���Զ�ִ��У׼
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET);
}

uint16_t AD_GetValue(void)
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);					//�������ADת��һ��
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);	//�ȴ�EOC��־λ�����ȴ�ADת������
	return ADC_GetConversionValue(ADC1);					//�����ݼĴ������õ�ADת���Ľ��
}

uint16_t AD2_GetValue(void)
{
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);					//�������ADת��һ��
	while (ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC) == RESET);	//�ȴ�EOC��־λ�����ȴ�ADת������
	return ADC_GetConversionValue(ADC2);					//�����ݼĴ������õ�ADת���Ľ��
}

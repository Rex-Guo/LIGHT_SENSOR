#include "sensor.h"
#include "Led.h"

void Sensor_Init()
{
	GPIO_InitTypeDef	GPIO_InitStruct;
	NVIC_InitTypeDef	NVIC_InitStruct;
	EXTI_InitTypeDef	EXTI_InitStruct;
	
	//����GPIOF���ж�ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	//����GPIOF_7
	GPIO_InitStruct.GPIO_Mode			= GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType		= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin			= GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd			= GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed		= GPIO_Speed_25MHz;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
	
	//�ж�ͨ������
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource7);
	
	//�����ж�
	EXTI_InitStruct.EXTI_Line			= EXTI_Line7;
	EXTI_InitStruct.EXTI_LineCmd	= ENABLE;
	EXTI_InitStruct.EXTI_Mode			= EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger	= EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	//�����ж�NVIC
	NVIC_InitStruct.NVIC_IRQChannel										= EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd								= ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority				= 0;
	NVIC_Init(&NVIC_InitStruct);
	
}

//EXTI9-5���жϴ���
void EXTI9_5_IRQHandler(void)
{
	if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7) == 1)Off_Led(0xf);
	else{
		On_Led(0xf);
	}
}

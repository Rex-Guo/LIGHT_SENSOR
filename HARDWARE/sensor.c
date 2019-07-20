#include "sensor.h"
#include "Led.h"

void Sensor_Init()
{
	GPIO_InitTypeDef	GPIO_InitStruct;
	NVIC_InitTypeDef	NVIC_InitStruct;
	EXTI_InitTypeDef	EXTI_InitStruct;
	
	//开启GPIOF，中断时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	//设置GPIOF_7
	GPIO_InitStruct.GPIO_Mode			= GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType		= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin			= GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd			= GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed		= GPIO_Speed_25MHz;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
	
	//中断通道设置
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource7);
	
	//设置中断
	EXTI_InitStruct.EXTI_Line			= EXTI_Line7;
	EXTI_InitStruct.EXTI_LineCmd	= ENABLE;
	EXTI_InitStruct.EXTI_Mode			= EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger	= EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	//开启中断NVIC
	NVIC_InitStruct.NVIC_IRQChannel										= EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd								= ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority	= 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority				= 0;
	NVIC_Init(&NVIC_InitStruct);
	
}

//EXTI9-5号中断处理
void EXTI9_5_IRQHandler(void)
{
	if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_7) == 1)Off_Led(0xf);
	else{
		On_Led(0xf);
	}
}

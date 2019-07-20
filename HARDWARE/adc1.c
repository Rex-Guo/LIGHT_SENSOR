#include "adc1.h"
#include "usart1.h"

void ADC3_Init()
{
	GPIO_InitTypeDef	GPIO_InitStruct;
	ADC_CommonInitTypeDef	ADC_CommonInitStruct;
	ADC_InitTypeDef		ADC_InitStruct;
	
	//开启GPIOF，ADC3时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
	
	//设置GPIOF_7
	GPIO_InitStruct.GPIO_Mode			= GPIO_Mode_AN;//模拟输入
	GPIO_InitStruct.GPIO_OType		= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin			= GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd			= GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed		= GPIO_Speed_2MHz;
	GPIO_Init(GPIOF, &GPIO_InitStruct);

	ADC_CommonInitStruct.ADC_Mode							= ADC_Mode_Independent;//独立模式
	ADC_CommonInitStruct.ADC_TwoSamplingDelay	= ADC_TwoSamplingDelay_5Cycles; //设置两个采样阶段之间的延迟周期数
	ADC_CommonInitStruct.ADC_DMAAccessMode		= ADC_DMAAccessMode_Disabled; //DMA模式禁止或者使能相应DMA模式
	ADC_CommonInitStruct.ADC_Prescaler				= ADC_Prescaler_Div4;	//设置ADC预分频器
	ADC_CommonInit(&ADC_CommonInitStruct);//初始化
	
	ADC_InitStruct.ADC_ContinuousConvMode		= DISABLE;//是否连续转换
	ADC_InitStruct.ADC_DataAlign						= ADC_DataAlign_Right;//右对齐
	ADC_InitStruct.ADC_ExternalTrigConvEdge	= ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发//ADC_ExternalTrigConvEdge_RisingFalling;//双沿触发
	ADC_InitStruct.ADC_NbrOfConversion			= 1;//1个转换在规则序列中
	ADC_InitStruct.ADC_Resolution						= ADC_Resolution_12b;
	ADC_InitStruct.ADC_ScanConvMode					= DISABLE;//非扫描模式
	ADC_Init(ADC3, &ADC_InitStruct);
	
	ADC_DiscModeChannelCountConfig(ADC3, 1);
	ADC_DiscModeCmd(ADC3, ENABLE);

}

uint16_t Read_ADC()
{
	ADC_Cmd(ADC3, ENABLE);//开启AD转换器
	ADC_RegularChannelConfig(ADC3,ADC_Channel_5, 1, ADC_SampleTime_480Cycles );
	ADC_SoftwareStartConv(ADC3);//使能指定的ADC1的软件转换启动功能
	while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC));//等待转换结束
	ADC_Cmd(ADC3, DISABLE);//关闭AD转换器
	return ADC_GetConversionValue(ADC3);           //返回最近一次ADC1规则组的转换结果
}

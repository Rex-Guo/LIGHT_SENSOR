#include "adc1.h"
#include "usart1.h"

void ADC3_Init()
{
	GPIO_InitTypeDef	GPIO_InitStruct;
	ADC_CommonInitTypeDef	ADC_CommonInitStruct;
	ADC_InitTypeDef		ADC_InitStruct;
	
	//����GPIOF��ADC3ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
	
	//����GPIOF_7
	GPIO_InitStruct.GPIO_Mode			= GPIO_Mode_AN;//ģ������
	GPIO_InitStruct.GPIO_OType		= GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin			= GPIO_Pin_7;
	GPIO_InitStruct.GPIO_PuPd			= GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed		= GPIO_Speed_2MHz;
	GPIO_Init(GPIOF, &GPIO_InitStruct);

	ADC_CommonInitStruct.ADC_Mode							= ADC_Mode_Independent;//����ģʽ
	ADC_CommonInitStruct.ADC_TwoSamplingDelay	= ADC_TwoSamplingDelay_5Cycles; //�������������׶�֮����ӳ�������
	ADC_CommonInitStruct.ADC_DMAAccessMode		= ADC_DMAAccessMode_Disabled; //DMAģʽ��ֹ����ʹ����ӦDMAģʽ
	ADC_CommonInitStruct.ADC_Prescaler				= ADC_Prescaler_Div4;	//����ADCԤ��Ƶ��
	ADC_CommonInit(&ADC_CommonInitStruct);//��ʼ��
	
	ADC_InitStruct.ADC_ContinuousConvMode		= DISABLE;//�Ƿ�����ת��
	ADC_InitStruct.ADC_DataAlign						= ADC_DataAlign_Right;//�Ҷ���
	ADC_InitStruct.ADC_ExternalTrigConvEdge	= ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������//ADC_ExternalTrigConvEdge_RisingFalling;//˫�ش���
	ADC_InitStruct.ADC_NbrOfConversion			= 1;//1��ת���ڹ���������
	ADC_InitStruct.ADC_Resolution						= ADC_Resolution_12b;
	ADC_InitStruct.ADC_ScanConvMode					= DISABLE;//��ɨ��ģʽ
	ADC_Init(ADC3, &ADC_InitStruct);
	
	ADC_DiscModeChannelCountConfig(ADC3, 1);
	ADC_DiscModeCmd(ADC3, ENABLE);

}

uint16_t Read_ADC()
{
	ADC_Cmd(ADC3, ENABLE);//����ADת����
	ADC_RegularChannelConfig(ADC3,ADC_Channel_5, 1, ADC_SampleTime_480Cycles );
	ADC_SoftwareStartConv(ADC3);//ʹ��ָ����ADC1�����ת����������
	while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC));//�ȴ�ת������
	ADC_Cmd(ADC3, DISABLE);//�ر�ADת����
	return ADC_GetConversionValue(ADC3);           //�������һ��ADC1�������ת�����
}

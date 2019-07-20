#include "Led.h"
#include "Wait_Clock.h"

/*
  * ��  �ܣ���ʼ��GPIOx
  * ��  ����void
  * ����ֵ��void
  *
*/
void Init(void)	
{
	//�����Ĵ�����
	GPIO_InitTypeDef GPIO_InitTypeDef;
	
	//����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOE, ENABLE);
	
	//����Ĵ�����
	GPIO_InitTypeDef.GPIO_Mode		= GPIO_Mode_OUT;
	GPIO_InitTypeDef.GPIO_Pin			= GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitTypeDef.GPIO_OType		= GPIO_OType_PP;
	GPIO_InitTypeDef.GPIO_PuPd		= GPIO_PuPd_UP;
	GPIO_InitTypeDef.GPIO_Speed		= GPIO_Speed_2MHz;
	
	//��ʼ���Ĵ�����F
	GPIO_Init(GPIOF, &GPIO_InitTypeDef);

	GPIO_InitTypeDef.GPIO_Pin		= GPIO_Pin_13 | GPIO_Pin_14;
	//��ʼ���Ĵ�����F
	GPIO_Init(GPIOE, &GPIO_InitTypeDef);
	
	//��ʼ����
	GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);
	GPIO_SetBits(GPIOE,GPIO_Pin_13 | GPIO_Pin_14);

}

void Off_Led(u8 led)
{
	//����
	if(!~(led | ~(0x1))){
		GPIO_ResetBits(GPIOF, GPIO_Pin_9);
	}
	if(!~(led | ~(0x1 << 1))){
		GPIO_ResetBits(GPIOF, GPIO_Pin_10);
	}
	if(!~(led | ~(0x1 << 2))){
		GPIO_ResetBits(GPIOE, GPIO_Pin_13);
	}
	if(!~(led | ~(0x1 << 3))){
		GPIO_ResetBits(GPIOE, GPIO_Pin_14);
	}
}

void On_Led(u8 led)
{
	//����
	if(!~(led | ~(0x1))){
		GPIO_SetBits(GPIOF, GPIO_Pin_9);
	}
	if(!~(led | ~(0x1 << 1))){
		GPIO_SetBits(GPIOF, GPIO_Pin_10);
	}
	if(!~(led | ~(0x1 << 2))){
		GPIO_SetBits(GPIOE, GPIO_Pin_13);
	}
	if(!~(led | ~(0x1 << 3))){
		GPIO_SetBits(GPIOE, GPIO_Pin_14);
	}
}

void Multi_Function(volatile int *n)
{
	int i = 0;
	if(*n == 1){
		Init();
		On_Led(B1111);
		for(i = 8; i > 1 && *n == 1; i = (i /2)){
			Off_Led((u8)i);
			delay_ms(500);
			On_Led(B1111);
			delay_ms(100);
		}

		for(i = 1; i <= 8 && *n == 1; i = i * 2){
			Off_Led((u8)i);
			delay_ms(500);
			On_Led(B1111);
			delay_ms(100);
		}
	}else if(*n == 2){
		Init();
		Off_Led(B1111);
		delay_ms(500);
		On_Led(B1111);
		delay_ms(500);
	}else if(*n == 3){

	}
}

#include "Led.h"
#include "Wait_Clock.h"

/*
  * 功  能：初始化GPIOx
  * 参  数：void
  * 返回值：void
  *
*/
void Init(void)	
{
	//声明寄存器组
	GPIO_InitTypeDef GPIO_InitTypeDef;
	
	//设置时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOE, ENABLE);
	
	//定义寄存器组
	GPIO_InitTypeDef.GPIO_Mode		= GPIO_Mode_OUT;
	GPIO_InitTypeDef.GPIO_Pin			= GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitTypeDef.GPIO_OType		= GPIO_OType_PP;
	GPIO_InitTypeDef.GPIO_PuPd		= GPIO_PuPd_UP;
	GPIO_InitTypeDef.GPIO_Speed		= GPIO_Speed_2MHz;
	
	//初始化寄存器组F
	GPIO_Init(GPIOF, &GPIO_InitTypeDef);

	GPIO_InitTypeDef.GPIO_Pin		= GPIO_Pin_13 | GPIO_Pin_14;
	//初始化寄存器组F
	GPIO_Init(GPIOE, &GPIO_InitTypeDef);
	
	//初始灯灭
	GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);
	GPIO_SetBits(GPIOE,GPIO_Pin_13 | GPIO_Pin_14);

}

void Off_Led(u8 led)
{
	//灯亮
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
	//灯灭
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

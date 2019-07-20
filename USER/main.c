#include "stm32f4xx.h"
#include "Wait_Clock.h"
#include "sensor.h"
#include "Led.h"
#include "adc1.h"
#include "usart1.h"


int main(void)
{
	uint16_t count = 0; 
	Systick_Init();
	Usart1_Init(115200);
	Init();
	printf("Init OK\r\n");
	
#if 0	//TTL信号模式
	Sensor_Init();
	while(1){
		
	}
#else	//ADC模式
	ADC3_Init();
	while(1){
		count = Read_ADC();
		printf("the:%d\r\n",count);
		if(count > 1500){
			Off_Led(0xf);
		}else{
			On_Led(0xf);
		}
		delay_s(1);
	}
#endif
	
}

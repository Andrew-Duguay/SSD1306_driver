#include "stm32f446xx.h"
#include "uart.h"
#include "adc.h"
#include <stdio.h>
#include <stdint.h>

//static void ADC_callback(void);
uint32_t sensor_val;


int main(void)
{
	//pa1_adc_interrupt_init();
	SCB->CPACR |= (0xF << 20);	//enable fpu. See Arm user guide
	uart2_rxtx_init();
	temp_sensor_init();

	while(1){
		sensor_val = temp_sensor_read();
		printf("Temp: %d F \n\r", (int)sensor_val);
	}
}

//static void ADC_callback(void){
//	sensor_val = ADC1->DR;
//	//printf("sensor value: %d \n\r", (int)sensor_val);
//}
//
////found in vector table in startup
//void ADC_IRQHandler(void){
//	//Check for EOC in SR
//	if((ADC1->SR & SR_EOC) != 0){
//		//clear eoc
//		ADC1->SR &=~ SR_EOC;
//		ADC_callback();
//	}
//
//}






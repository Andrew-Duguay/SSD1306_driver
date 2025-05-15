#include "stm32f446xx.h"
#include "uart.h"
#include "adc.h"
#include <stdio.h>
#include <stdint.h>
#include "ssd1306.h"
#include "graphics.h"

//static void ADC_callback(void);
uint32_t sensor_val;

int main(void)
{
	I2C1_init();
	OLED_display_init();
	//uart2_rxtx_init();
	//temp_sensor_init();

	clearDisplay();
	drawRect(30,30,30,30);
	display();
	for(int i = 0; i < 3000000; i++){}
	eraseRect(30,30,30,30);
	display();
	for(int i = 0; i < 3000000; i++){}
	drawLine(-1,-1,130,65);
	display();
	for(int i = 0; i < 3000000; i++){}
	eraseLine(-1,-1,130,65);
	display();
	for(int i = 0; i < 3000000; i++){}
	drawLine(130,65,-1,-1);
	display();
	for(int i = 0; i < 3000000; i++){}
	eraseLine(130,65,-1,-1);
	display();
	for(int i = 0; i < 3000000; i++){}
	while(1){}
}







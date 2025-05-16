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
	clearDisplay();
	display();
	int x = 64, y = 32, r = 6;
	int dy = 2, dx = 2, dr = 2;

	while(1){
		drawCircle(x,y,r);
		display();
		eraseCircle(x,y,r);
		x += dx;
		y += dy;
		if(x <= r || x >= SCREEN_WIDTH - r){
			dx *= -1;

		}
		if(y <= r || y >= SCREEN_HEIGHT - r){
			dy *= -1;
	}

}







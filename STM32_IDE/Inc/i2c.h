#ifndef I2C_H
#define I2C_H

#include "stm32f446xx.h"

void I2C1_init();

void I2C1_read(char slave_add, char mem_add, char* data);

void I2C1_burstRead(char slave_add, char mem_add, int n, char* data);

void I2C1_burstWrite(char slave_add, char mem_add, int n, char* data);

#endif

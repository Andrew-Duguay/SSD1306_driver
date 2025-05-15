################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/graphics.c \
../Src/i2c.c \
../Src/main.c \
../Src/ssd1306.c \
../Src/uart.c 

OBJS += \
./Src/adc.o \
./Src/graphics.o \
./Src/i2c.o \
./Src/main.o \
./Src/ssd1306.o \
./Src/uart.o 

C_DEPS += \
./Src/adc.d \
./Src/graphics.d \
./Src/i2c.d \
./Src/main.d \
./Src/ssd1306.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -DSTM32F446xx -c -I../Inc -I"C:/Users/andre/STM32CubeIDE/workspace_getting_started/chip_headers/CMSIS/Include" -I"C:/Users/andre/STM32CubeIDE/workspace_getting_started/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adc.cyclo ./Src/adc.d ./Src/adc.o ./Src/adc.su ./Src/graphics.cyclo ./Src/graphics.d ./Src/graphics.o ./Src/graphics.su ./Src/i2c.cyclo ./Src/i2c.d ./Src/i2c.o ./Src/i2c.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/ssd1306.cyclo ./Src/ssd1306.d ./Src/ssd1306.o ./Src/ssd1306.su ./Src/uart.cyclo ./Src/uart.d ./Src/uart.o ./Src/uart.su

.PHONY: clean-Src


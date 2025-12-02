################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/led_driver.c \
../Library/shell.c \
../Library/uart_driver.c 

OBJS += \
./Library/led_driver.o \
./Library/shell.o \
./Library/uart_driver.o 

C_DEPS += \
./Library/led_driver.d \
./Library/shell.d \
./Library/uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Library/%.o Library/%.su Library/%.cyclo: ../Library/%.c Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/surendar/STM32CubeIDE/Emedded_Shell/Library" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Library

clean-Library:
	-$(RM) ./Library/led_driver.cyclo ./Library/led_driver.d ./Library/led_driver.o ./Library/led_driver.su ./Library/shell.cyclo ./Library/shell.d ./Library/shell.o ./Library/shell.su ./Library/uart_driver.cyclo ./Library/uart_driver.d ./Library/uart_driver.o ./Library/uart_driver.su

.PHONY: clean-Library


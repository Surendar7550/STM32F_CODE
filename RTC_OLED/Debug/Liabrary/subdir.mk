################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Liabrary/ds1302.c \
../Liabrary/oled_ssd1306.c 

OBJS += \
./Liabrary/ds1302.o \
./Liabrary/oled_ssd1306.o 

C_DEPS += \
./Liabrary/ds1302.d \
./Liabrary/oled_ssd1306.d 


# Each subdirectory must supply rules for building sources it contributes
Liabrary/%.o Liabrary/%.su Liabrary/%.cyclo: ../Liabrary/%.c Liabrary/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Vact_Tech/STM32CubeIDE/CRC/SURENDAR/RTC_OLED/Liabrary" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Liabrary

clean-Liabrary:
	-$(RM) ./Liabrary/ds1302.cyclo ./Liabrary/ds1302.d ./Liabrary/ds1302.o ./Liabrary/ds1302.su ./Liabrary/oled_ssd1306.cyclo ./Liabrary/oled_ssd1306.d ./Liabrary/oled_ssd1306.o ./Liabrary/oled_ssd1306.su

.PHONY: clean-Liabrary


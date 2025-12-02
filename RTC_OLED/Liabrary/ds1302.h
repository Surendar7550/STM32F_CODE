#ifndef DS1302_H
#define DS1302_H

#include "stm32f4xx_hal.h"

void DS1302_GPIO_Init(void);
void DS1302_WriteRegister(uint8_t reg, uint8_t data);
uint8_t DS1302_ReadRegister(uint8_t reg);
void DS1302_ReadTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds);

#endif

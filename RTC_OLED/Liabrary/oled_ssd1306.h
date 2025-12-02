#ifndef OLED_SSD1306_H
#define OLED_SSD1306_H

#include "stm32f4xx_hal.h"

void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawChar(uint8_t x, uint8_t page, char c);
void OLED_DrawString(uint8_t x, uint8_t page, char *str);

#endif

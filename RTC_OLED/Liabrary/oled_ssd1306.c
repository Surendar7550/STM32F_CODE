#include "oled_ssd1306.h"
#include <string.h>
#include <stdio.h>

extern I2C_HandleTypeDef hi2c2; // Make sure MX_I2C2_Init() is called in main

#define OLED_I2C_ADDR (0x3C << 1)  // 7-bit addr shifted for HAL

// 5x7 font for digits 0-9 and colon ':'
static const uint8_t font5x7[][5] = {
    // '0'
    {0x3E, 0x51, 0x49, 0x45, 0x3E},
    // '1'
    {0x00, 0x42, 0x7F, 0x40, 0x00},
    // '2'
    {0x42, 0x61, 0x51, 0x49, 0x46},
    // '3'
    {0x21, 0x41, 0x45, 0x4B, 0x31},
    // '4'
    {0x18, 0x14, 0x12, 0x7F, 0x10},
    // '5'
    {0x27, 0x45, 0x45, 0x45, 0x39},
    // '6'
    {0x3C, 0x4A, 0x49, 0x49, 0x30},
    // '7'
    {0x01, 0x71, 0x09, 0x05, 0x03},
    // '8'
    {0x36, 0x49, 0x49, 0x49, 0x36},
    // '9'
    {0x06, 0x49, 0x49, 0x29, 0x1E},
    // ':'
    {0x00, 0x36, 0x36, 0x00, 0x00}
};

static void OLED_WriteCommand(uint8_t cmd) {
    uint8_t data[2] = {0x00, cmd};
    HAL_I2C_Master_Transmit(&hi2c2, OLED_I2C_ADDR, data, 2, HAL_MAX_DELAY);
}

static void OLED_WriteData(uint8_t *data, uint16_t size) {
    uint8_t buffer[size + 1];
    buffer[0] = 0x40;
    memcpy(&buffer[1], data, size);
    HAL_I2C_Master_Transmit(&hi2c2, OLED_I2C_ADDR, buffer, size + 1, HAL_MAX_DELAY);
}

void OLED_Init(void) {
    HAL_Delay(100);

    OLED_WriteCommand(0xAE); // Display OFF
    OLED_WriteCommand(0x20); // Memory addressing mode
    OLED_WriteCommand(0x10); // Page addressing mode
    OLED_WriteCommand(0xB0); // Page start address
    OLED_WriteCommand(0xC8); // COM scan direction remapped
    OLED_WriteCommand(0x00); // low col start addr
    OLED_WriteCommand(0x10); // high col start addr
    OLED_WriteCommand(0x40); // line start addr
    OLED_WriteCommand(0x81); // contrast
    OLED_WriteCommand(0xFF);
    OLED_WriteCommand(0xA1); // segment remap
}

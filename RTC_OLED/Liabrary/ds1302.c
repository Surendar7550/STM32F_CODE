#include "ds1302.h"

// GPIO Pin definitions
#define DS1302_CLK_PIN      GPIO_PIN_0
#define DS1302_IO_PIN       GPIO_PIN_1
#define DS1302_CE_PIN       GPIO_PIN_2
#define DS1302_GPIO_PORT    GPIOA

// Delay for timing (adjust if needed)
static void DS1302_Delay(void) {
    for(volatile int i=0; i<100; i++);
}

// Pin mode helpers for bidirectional IO pin
static void DS1302_IO_Output(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DS1302_IO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DS1302_GPIO_PORT, &GPIO_InitStruct);
}

static void DS1302_IO_Input(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DS1302_IO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DS1302_GPIO_PORT, &GPIO_InitStruct);
}

// Control CE pin
static void DS1302_CE_High(void) {
    HAL_GPIO_WritePin(DS1302_GPIO_PORT, DS1302_CE_PIN, GPIO_PIN_SET);
}

static void DS1302_CE_Low(void) {
    HAL_GPIO_WritePin(DS1302_GPIO_PORT, DS1302_CE_PIN, GPIO_PIN_RESET);
}

// Write one bit to DS1302
static void DS1302_WriteBit(uint8_t bit) {
    DS1302_IO_Output();
    HAL_GPIO_WritePin(DS1302_GPIO_PORT, DS1302_IO_PIN, bit ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(DS1302_GPIO_PORT, DS1302_CLK_PIN, GPIO_PIN_SET);
    DS1302_Delay();

    HAL_GPIO_WritePin(DS1302_GPIO_PORT, DS1302_CLK_PIN, GPIO_PIN_RESET);
    DS1302_Delay();
}

// Read one bit from DS1302
static uint8_t DS1302_ReadBit(void) {
    uint8_t bit;

    DS1302_IO_Input();

    HAL_GPIO_WritePin(DS1302_GPIO_PORT, DS1302_CLK_PIN, GPIO_PIN_SET);
    DS1302_Delay();

    bit = HAL_GPIO_ReadPin(DS1302_GPIO_PORT, DS1302_IO_PIN);

    HAL_GPIO_WritePin(DS1302_GPIO_PORT, DS1302_CLK_PIN, GPIO_PIN_RESET);
    DS1302_Delay();

    return bit;
}

// Write one byte (LSB first)
static void DS1302_WriteByte(uint8_t byte) {
    for(int i = 0; i < 8; i++) {
        DS1302_WriteBit(byte & 0x01);
        byte >>= 1;
    }
}

// Read one byte (LSB first)
static uint8_t DS1302_ReadByte(void) {
    uint8_t byte = 0;
    for(int i = 0; i < 8; i++) {
        uint8_t bit = DS1302_ReadBit();
        byte |= (bit << i);
    }
    return byte;
}

// Convert BCD to decimal
static uint8_t BCD_To_Dec(uint8_t val) {
    return ((val >> 4) * 10) + (val & 0x0F);
}

// Initialize GPIOs for DS1302
void DS1302_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    // CLK and CE output
    GPIO_InitStruct.Pin = DS1302_CLK_PIN | DS1302_CE_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DS1302_GPIO_PORT, &GPIO_InitStruct);

    // IO as output initially
    DS1302_IO_Output();
    HAL_GPIO_WritePin(DS1302_GPIO_PORT, DS1302_IO_PIN, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(DS1302_GPIO_PORT, DS1302_CLK_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DS1302_GPIO_PORT, DS1302_CE_PIN, GPIO_PIN_RESET);
}

// Write to DS1302 register
void DS1302_WriteRegister(uint8_t reg, uint8_t data) {
    DS1302_CE_High();
    DS1302_WriteByte((reg << 1) & 0xFE); // Write command (LSB=0)
    DS1302_WriteByte(data);
    DS1302_CE_Low();
}

// Read from DS1302 register
uint8_t DS1302_ReadRegister(uint8_t reg) {
    uint8_t data;
    DS1302_CE_High();
    DS1302_WriteByte(((reg << 1) & 0xFE) | 0x01); // Read command (LSB=1)
    data = DS1302_ReadByte();
    DS1302_CE_Low();
    return data;
}

// Read time registers (hours, minutes, seconds)
void DS1302_ReadTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds) {
    *seconds = BCD_To_Dec(DS1302_ReadRegister(0x00));
    *minutes = BCD_To_Dec(DS1302_ReadRegister(0x01));
    *hours   = BCD_To_Dec(DS1302_ReadRegister(0x02));
}


/*
 * uart_driver.c
 *
 *  Created on: Jul 26, 2025
 *      Author: surendar
 */


#include "uart_driver.h"
#include "main.h"
#include <string.h>
extern UART_HandleTypeDef huart2;

void uart_send(const char *s) {
    HAL_UART_Transmit(&huart2, (uint8_t *)s, strlen(s), HAL_MAX_DELAY);
}

void uart_write(char c) {
    HAL_UART_Transmit(&huart2, (uint8_t *)&c, 1, HAL_MAX_DELAY);
}

bool uart_read(char *c) {
    return HAL_UART_Receive(&huart2, (uint8_t *)c, 1, 0) == HAL_OK;
}

/*
 * utils.c
 *
 *  Created on: Jul 29, 2025
 *      Author: surendar
 */


#include "utils.h"
#include <string.h>

void print(const char *msg) {
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
}

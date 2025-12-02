/*
 * fsm.c
 *
 *  Created on: Jul 29, 2025
 *      Author: surendar
 */

#include "fsm.h"
#include "main.h"
#include <stdio.h>

extern UART_HandleTypeDef huart2;

static FSM_State current_state;

void FSM_Init(void) {
    current_state = STATE_IDLE;
    char msg[] = "State: IDLE\r\n";
    HAL_UART_Transmit(&huart2, (uint8_t*)msg, sizeof(msg) - 1, HAL_MAX_DELAY);
}

void FSM_Update(char input) {
    switch (current_state) {
        case STATE_IDLE:
            if (input == 'i') { // insert coin
                current_state = STATE_SELECTING_PRODUCT;
                char msg[] = "Coin Inserted. Select Product.\r\n";
                HAL_UART_Transmit(&huart2, (uint8_t*)msg, sizeof(msg) - 1, HAL_MAX_DELAY);
            }
            break;

        case STATE_SELECTING_PRODUCT:
            if (input == 'p') { // product selected
                current_state = STATE_PROCESSING_PAYMENT;
                char msg[] = "Product Selected. Processing Payment...\r\n";
                HAL_UART_Transmit(&huart2, (uint8_t*)msg, sizeof(msg) - 1, HAL_MAX_DELAY);
            }
            break;

        case STATE_PROCESSING_PAYMENT:
            if (input == 'c') { // payment complete
                current_state = STATE_DISPENSING_PRODUCT;
                char msg[] = "Payment Complete. Dispensing Product...\r\n";
                HAL_UART_Transmit(&huart2, (uint8_t*)msg, sizeof(msg) - 1, HAL_MAX_DELAY);

                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET); // LED ON
                HAL_Delay(1000);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); // LED OFF

                current_state = STATE_IDLE;
                char done[] = "Dispensed. Returning to IDLE.\r\n";
                HAL_UART_Transmit(&huart2, (uint8_t*)done, sizeof(done) - 1, HAL_MAX_DELAY);
            }
            break;

        default:
            break;
    }
}


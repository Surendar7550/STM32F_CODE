/*
 * led_driver.c
 *
 *  Created on: Jul 26, 2025
 *      Author: surendar
 */


#include "led_driver.h"
#include "main.h"

static int led_state = 0;

void led_on(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    led_state = 1;
}

void led_off(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    led_state = 0;
}

int get_led_status(void) {
    return led_state;
}

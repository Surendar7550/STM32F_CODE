/*
 * shell.c
 *
 *  Created on: Jul 26, 2025
 *      Author: surendar
 */


#include "shell.h"
#include "uart_driver.h"
#include "led_driver.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#define CMD_LEN 64
static char cmd[CMD_LEN];
static uint8_t cmd_index = 0;

void shell_init(void) {
    uart_send("\r\n[Embedded Shell Ready]\r\n> ");
}

void shell_process(void) {
    char c;
    if (uart_read(&c)) {
        if (c == '\r' || c == '\n') {
        	cmd[cmd_index] = '\0';
            uart_send("\r\n");
            if (strcmp(cmd, "LED ON") == 0) {
                led_on();
                uart_send("LED turned ON\r\n");
            } else if (strcmp(cmd, "LED OFF") == 0) {
                led_off();
                uart_send("LED turned OFF\r\n");
            } else if (strcmp(cmd, "STATUS") == 0) {
                uart_send(get_led_status() ? "LED is ON\r\n" : "LED is OFF\r\n");
            } else if (strcmp(cmd, "HELP") == 0) {
                uart_send("Commands: LED ON, LED OFF, STATUS, HELP\r\n");
            } else {
                uart_send("Unknown command\r\n");
            }
            cmd_index = 0;
            uart_send("> ");
        } else if (cmd_index < CMD_LEN - 1) {
        	cmd[cmd_index++] = c;
            uart_write(c);  // echo
        }
    }
}

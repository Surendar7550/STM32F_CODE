/*
 * uart_driver.h
 *
 *  Created on: Jul 26, 2025
 *      Author: surendar
 */

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include <stdbool.h>

void uart_send(const char *s);
void uart_write(char c);
bool uart_read(char *c);


#endif /* UART_DRIVER_H_ */

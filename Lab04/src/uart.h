/*
 * uart.h
 *
 *  Created on: 10 de nov de 2015
 *      Author: aluno
 */

#ifndef SRC_UART_H_
#define SRC_UART_H_

#define byte uint8_t

#include <avr/io.h>

void turnOnRxOffTx() {
	UCSR0B = 0x98;
}

void turnOnRxOnTx() {
	UCSR0B = 0xB8;
}

/// Configure serial to 9600 8N1
void uart_setup() {
	UBRR0H = 0;
	UBRR0L = 103;
	UCSR0C = 0x06;
	turnOnRxOffTx();
}

int uart_has_data() {
	return (UCSR0A & 0x20);
}

int uart_ready() {
	return (UCSR0A & 0x80);
}

byte uart_receive_data() {
	while (!uart_has_data())
		;
	return UDR0;
}

void uart_send_data(byte data) {
	while (!uart_ready())
		;
	UDR0 = data;
	turnOnRxOffTx();
}

#endif /* SRC_UART_H_ */

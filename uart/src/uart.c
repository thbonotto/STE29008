/*
 * uart.c
 *
 *  Created on: 27 de out de 2015
 *      Author: aluno
 */

#include <avr/io.h>

uint8_t data;

void setup() {
	data = 0;
	UBRR0L = 103;
	UBRR0H = 0;
	UCSR0C = 0x06;
	UCSR0B = 0x18;
}

int uart_has_data(){
	return(UCSR0A & 0x80);
}

int uart_ready() {
	return (UCSR0A & 0x20);
}

void uart_receive_data(){
	while(!uart_has_data());
		data = UDR0;;
}

void uart_send_data(){
	while(!uart_ready());
	UDR0 = data;
}

void loop(){
	if(uart_has_data()) {
		uart_receive_data();
		data++;
		uart_send_data();
	}
}

int main(){
	setup();
	while(1)
		loop();
}

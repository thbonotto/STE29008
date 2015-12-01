#include <avr/io.h>
#include <avr/interrupt.h>
#include "queue.h"
#include "milli_counter.h"

#define byte uint8_t

#define F_CPU 16000000UL

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
	while (!uart_ready())		;
	UDR0 = data;
	UCSR0B = 0x98;
}

// We need 2 buffers, one to store data received from serial, and another to store data that will be sent through the serial
Queue tx_buf;
Queue rx_buf;

ISR(USART_RX_vect){
	cli();
	push(&rx_buf,uart_receive_data());
	sei();
}


ISR(USART_UDRE_vect){
	cli();
	uart_send_data(pop(&tx_buf));
	sei();
}

void setup(){
	init(&tx_buf);
	init(&rx_buf);
	UBRR0H = 0;
	//  UBRR0L = 103; //9600
		UBRR0L = 51; //19200
	//	UBRR0L = 16; //57600
	//	UBRR0L = 7; //115200
	UCSR0C = 0x06;
	UCSR0B = 0xB8;
	sei();

}

void loop(){
	if(tx_buf.size)
		UCSR0B = 0xB8;

	/**
	 * Build a graph where the x axis is the processing time (P={1,4,8}, ms)
	 * and the y axis is the minimum buffer size for a 1-second data transfer burst;
	 */
	milli_counter_start();
		while(milli_counter() < 1);
	
	if(rx_buf.size)
		push(&tx_buf, pop(&rx_buf));
}

int main(void) {
	setup();
    //Implement loopback application - just remove older byte in the receive queue and enqueue it on the output buffer
    while(1)
    	loop();
}



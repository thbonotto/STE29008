#include <avr/io.h>
#include <avr/interrupt.h>
#include "milli_counter.h"

#define F_CPU 16000000UL
#define BUFFER_SIZE 47
#define byte uint8_t

/**
 * Build a graph where the x axis is the processing time (P={1,4,8}, ms)
 * and the y axis is the minimum buffer size for a 1-second data transfer burst;
 */
const milli_counter_t getDelay = 8;


typedef volatile struct {
    int headPos;
    int tailPos;
    int size;
    byte buffer[BUFFER_SIZE];
} Queue;


// We need 2 buffers, one to store data received from serial, and another to store data that will be sent through the serial
Queue tx_buf;
Queue rx_buf;

void push(Queue * fila, byte data){
	if(fila->size < (BUFFER_SIZE-1)){
		fila->buffer[fila->tailPos] = data;
		fila->size++;
		if(fila->tailPos!=BUFFER_SIZE-1)
			fila->tailPos++;
		else
			fila->tailPos = 0;
	}
}

byte pop(Queue * fila){

	byte data = 0;

	if(fila->size > 0) {
		data = fila->buffer[fila->headPos];
		fila->size--;
		if(fila->headPos!=BUFFER_SIZE-1)
			fila->headPos++;
		else
			fila->headPos = 0;
	}
	return data;
}

void init(Queue * fila){
	unsigned int i;
	fila->tailPos=0;
	fila->headPos=0;
	fila->size=0;
	for(i=0; i < BUFFER_SIZE; i++)
		fila->buffer[i]=0;
}

int uart_has_data(){
	return (UCSR0A & 0x20);
}

int uart_ready(){
	return (UCSR0A & 0x80);
}

void uart_receive_data(){
	while(!uart_has_data());
	push(&rx_buf, UDR0);
}

void uart_send_data(){
	while(!uart_has_data());
	UDR0 = pop(&tx_buf);
	UCSR0B = 0x98;
}

ISR(USART_RX_vect) {
	cli();
	push(&tx_buf, UDR0);
	sei();

}

ISR(USART_UDRE_vect) {
	cli();
	uart_send_data();
	sei();
}
/**
 * Plot in this graph curves for different UART bitrates (B={19200,57600,115200}, bps).
 * @UBRR0L 9600 = 103; 19200 = 51; 57600 = 16; 115200 = 7;
 */
void setup(){
	UBRR0H = 0;
	UBRR0L = 16;
	UCSR0C = 0x06;
	UCSR0B = 0x98;
	init(&tx_buf);
	init(&rx_buf);
    sei();

}

void loop(){

	if(tx_buf.size > 0)
		UCSR0B = 0xB8;

	if(rx_buf.size > 0) {
		push(&tx_buf,pop(&rx_buf));
		milli_counter_start();
		while(milli_counter()<getDelay);
	}

}

int main (){
	setup();
	//Implement loopback application - just remove older byte in the receive queue and enqueue it on the output buffer
	while(1)
		loop();

}

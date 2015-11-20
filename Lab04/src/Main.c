#include <avr/io.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "queue.h"
#include "milli_counter.h"

// We need 2 buffers, one to store data received from serial, and another to store data that will be sent through the serial
Queue tx_buf;
Queue rx_buf;

// Finished sending one byte
void tx_interrupt_handler(){
    uart_send_data(pop(&tx_buf));
}

// Finished receiving one byte
void rx_interrupt_handler(){
	push(&rx_buf,uart_receive_data());
}

int rx_buffer_has_data(){
	return rx_buf.size;
}
int tx_buffer_has_data(){
	return tx_buf.size;
}

ISR(USART_RX_vect){
	cli();
	rx_interrupt_handler();
	sei();
}


ISR(USART_UDRE_vect){
	cli();
	tx_interrupt_handler();
	sei();
}

void setup(){
	init(&tx_buf);
	init(&rx_buf);
	uart_setup();
	sei();

}

void loop(){
	if(tx_buffer_has_data())
		turnOnRxOnTx();

	milli_counter_start();
		while(milli_counter()<TIME);
	
	if(rx_buffer_has_data())
		push(&tx_buf, pop(&rx_buf));
}

int main(void) {
	setup();
    //Implement loopback application - just remove older byte in the receive queue and enqueue it on the output buffer
    while(1)
    	loop();
}



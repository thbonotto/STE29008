/*
 * Uart.h
 *
 *  Created on: Dec 1, 2015
 *      Author: thiago.b
 */

#include "Uart.h"
#include "avr/io.h"
#include "avr/interrupt.h"

Uart& Uart::instance = *static_cast<Uart*>(0);

ISR(USART_RX_vect ) {
	Uart::getInstance().getRxBuffer().push(UDR0);
}

ISR(USART_UDRE_vect ) {
	if (Uart::getInstance().getTxBuffer().has_data())
		UDR0 = Uart::getInstance().getTxBuffer().pop();
	else
		UCSR0B &= ~0x20;
}

Uart::Uart() {
	UBRR0H = 0;
	UBRR0L = 103; //9600
	//	UBRR0L = 51; //19200
	//	UBRR0L = 16; //57600
	//	UBRR0L = 7; //115200
	UCSR0C = 0x06;
	turnOnRxOffTx();
	instance=*this;
}
Uart::~Uart() {

}

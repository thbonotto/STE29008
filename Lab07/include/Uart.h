/*
 * Uart.h
 *
 *  Created on: Dec 1, 2015
 *      Author: thiago.b
 */

#pragma once 

#define byte uint8_t

#include <avr/io.h>
#include "Circular_FIFO.h"

#define F_CPU 16000000UL

const unsigned int BUFFER_SIZE=23;

class Uart {
public:
	Uart();
	virtual ~Uart();

	static Uart& getInstance(){
			return instance;
		}

	inline void turnOnRxOffTx() {
		UCSR0B = 0x98;
	}

	inline void turnOnRxOnTx() {
		UCSR0B = 0xB8;
	}

	inline bool has_data() {
		return Uart::getInstance().getRxBuffer().has_data();
	}

	inline int uart_ready() {
		return (UCSR0A & 0x80);
	}

	void post(byte data){
		 this->tx_buf.push(data);
		 UCSR0B |= 0x20;
	}

	byte get(){
		return rx_buf.pop();
	}

	Circular_FIFO<byte,BUFFER_SIZE>& getTxBuffer(){
		return this->tx_buf;
	}

	Circular_FIFO<byte,BUFFER_SIZE>& getRxBuffer(){
			return this->rx_buf;
		}

private:

	byte uart_receive_data();

	void uart_send_data(byte data);

	static Uart& instance;


	Circular_FIFO<byte,BUFFER_SIZE> tx_buf;
	Circular_FIFO<byte,BUFFER_SIZE> rx_buf;

};

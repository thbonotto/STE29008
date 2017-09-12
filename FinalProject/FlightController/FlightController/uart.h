#ifndef UART_H_
#define UART_H_

#include "Circular_FIFO.h"
#include <stdint.h>

class Uart {
private:
    static Uart uart;
	static const int Buffer_Size = 23;

public:
	Uart();
	bool has_data();
	void put(uint8_t c);
	int8_t get();

	static void rx_interrupt_handler();
	static void empty_interrupt_handler();
	static void interruptoff();
	static void interrupton();

	Circular_FIFO<uint8_t,Buffer_Size> rx;
	Circular_FIFO<uint8_t,Buffer_Size> tx;
};

#endif /* UART_H_ */

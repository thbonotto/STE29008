#pragma once
#include <avr/io.h>

class Communicator {
public:
	Communicator();
	virtual ~Communicator();
	uint8_t getByte();
	bool dataAvaliable();
	void sendByte(uint8_t data);
};

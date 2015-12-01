/*
 * ADConverter.h
 *
 *  Created on: Dec 1, 2015
 *      Author: thiago.b
 */

#pragma once 

#include <avr/io.h>

#include "Circular_FIFO.h"

class ADConverter {

public:

	enum Frequency{ //valor do ADPS2:0 do ADCSRA/Fator de divisão
		F8M = 0x00,
		F4M = 0x02,
		F2M = 0x03,
		F1M = 0x04,
		F500k = 0x05,
		F250k = 0x06,
		F125k = 0x07
	};

	enum Reference{ //ADMUX 7:6 - REFS1:0
		VCC = 0x00, //vcc_interno = 5v
		AREF = 0x01, // vcc externo
		INTERNAL1V1 = 0x03 // tensão de 1,1v para calibrar
	};

	enum Channel { //ADMUX 3:0 - MUX3:0
		CHANNEL_0 = 0x00,
		CHANNEL_1 = 0x01,
		CHANNEL_2 = 0x02,
		CHANNEL_3 = 0x03,
		CHANNEL_4 = 0x04,
		CHANNEL_5 = 0x05,
		CHANNEL_6 = 0x06,
		CHANNEL_7 = 0x07,
		CHANNEL_8 = 0x08,
		INPUT_1V1 = 0x0E, // tensão de 1,1v para calibrar
		GND = 0x0F
	};


	enum Mode{  //ADTS2:0
		FREE_RUNNING = 0x00,
		TRIG_ANALOG_CMP = 0x01,
		TRIG_EXT_INT = 0x02,
		TRIG_TIMER0_CMPA = 0x03,
		TRIG_TIMER0_OVERFLOW = 0x04,
		TRIG_TIMER1_CMPB = 0x05,
		TRIG_TIMER1_OVERFLOW = 0x06,
		TRIG_TIMER1_CAPT_EVENT = 0x07,
		SINGLE_SHOT = 0x08 //se esse modo => ADATE = 0
	};

	ADConverter();
	ADConverter(const Channel& channel, const Frequency& freq, Reference ref, Mode mode);
	virtual ~ADConverter();
	int read();
	void use_interrupts(); //liga as interrupções
	int get_raw(); //0-1023
	int get_volt(); // mV
	int get_ref(); //mV-Referencia
	int RMS(const int& repeat);

private:
	Circular_FIFO<long, 44 > buffer;

	void enable();

};

/* ADCONVERTER_H_ */


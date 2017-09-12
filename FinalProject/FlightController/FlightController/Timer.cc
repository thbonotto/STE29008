/*
 * Timer.cpp
 *
 *  Created on: Dec 8, 2015
 *      Author: ebroering
 */

#include "Timer.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

Timer * Timer::timer;


ISR(TIMER0_OVF_vect) {
	Timer::handler();
}
void Timer::handler(){
	Timer::getInstance()->ticks++;
}

void operator delete(void * p) {
	free(p);
}


Timer::Timer(unsigned long freq) {
	this->timer = this;
	this->freq = freq;
	TCCR0B	=	0x01;
	int div = 0;
	if(freq > 62500){
		div = 1;
	}
	else if(freq < 62500 && freq > 7812){
		div = 8;
		TCCR0B	=	TCCR0B | 0x02;
	}else if(freq < 7812 && freq > 976){
		div = 64;
		TCCR0B	=	TCCR0B | 0x03;
	}else if(freq < 976 && freq > 244){
		div = 256;
		TCCR0B	=	TCCR0B | 0x04;
	}
	else if(freq < 244 && freq > 61){
			div = 1024;
			TCCR0B	=	TCCR0B | 0x05;
	}
	TIMSK0	=	0x01;
	TCNT0 = freq;
	us_ticks = (1000000/this->freq);
}


Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

void Timer::start(){
	TCCR0B	=	0x01;
}

void Timer::stop(){
	TCCR0B	=	0x00;
}

void Timer::reset(){
	TCNT0	=	0x00;
}

unsigned long Timer::get_microseconds(){
	return this->ticks*us_ticks;
}







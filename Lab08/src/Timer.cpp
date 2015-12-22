/*
 * Timer.cpp
 *
 *  Created on: 22 de dez de 2015
 *      Author: aluno
 */
#include <avr/interrupt.h>

#include "Timer.h"

Timer * Timer::timer=0;

Timer::Timer(unsigned long _freq) : freq(_freq) {
    TCNT0 = 0xF0; //16 clock cycles
    TIMSK0 = 0x01; //Set TOIE bit
}
Timer::~Timer(){

}

void Timer::start(){
	// inicia contagem
	TCCR0B = 0x05; //Init Timer0, normal, prescalar = 1024
}
void Timer::reset(){
	// zera contagem
}
void Timer::stop(){
	// para contagem
}

unsigned long long Timer::microseconds(){
	return ticks*10000;
}

void Timer::isr_handler(){
	TCNT0 = 0xF0;
	ticks++;
}

/* TIME_H */





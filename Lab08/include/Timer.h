 /*
* Timer.h
*
* Created on: 8 de dez de 2015
* Author: Arliones
*/
#pragma once

#include <stdlib.h>

class Timer {
public:
Timer(unsigned long _freq);
virtual ~Timer();

void start(); // inicia contagem
void reset(); // zera contagem
void stop(); // para contagem

void restart() {
	stop();
	reset();
	start();
}

unsigned long long microseconds();

void isr_handler();

static Timer * instance() { return timer; }

void operator delete(void * p) // or delete(void *, std::size_t)
{
	free(p);
}

private:
static Timer * timer;

unsigned long long freq;
volatile unsigned long long ticks;
};

/* TIME_H */

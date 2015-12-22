#include <avr/io.h>
#include <avr/interrupt.h>

#include "BetaNTC.h"
#include "ADConverter.h"
#include "Timer.h"


static const unsigned long long FREQ = 16000000/256; //Hz
static const unsigned long long PERIOD = 16; // ms

ISR(TIMER0_OVF_vect) {
	Timer::instance()->isr_handler();
}

void adc(){
	ADConverter adc;
	long int um=1l;
	    BetaNTC sensor(um,um,um);
	    while(1) {
	    	sensor.getTemperature(adc.getBuffer().pop());
	    }
}
void timer(){
	Timer _Timer(FREQ);
	DDRB = 0xFF;
	sei();
	while(true){
		_Timer.restart();
		while(_Timer.microseconds() < 500000);
		PORTB = ~ PORTB;
	}
}

int main(void) {
   timer();
}


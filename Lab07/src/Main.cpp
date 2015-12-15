#include "NTC.h"
#include "ADConverter.h"
#include "Timer.h"

#include <avr/io.h>
#include <avr/interrupt.h>

static const unsigned long long FREQ = 16000000/256; //Hz
static const unsigned long long PERIOD = 16; // ms

void adc(){
	ADConverter adc;
	    NTC sensor{};
	    while(1) {
	    	sensor.getTemperature(adc.getBuffer().pop());
	    }
}

void timer(){
	Timer timer(FREQ);
	DDRB = 0xFF;
	sei();
	while(true){
		timer.restart();
		while(timer.microseconds() < 500000);
		PORTB = ~ PORTB;
	}
}

int main(void) {
    return 0;
}


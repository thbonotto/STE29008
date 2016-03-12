#include <avr/io.h>
#include <avr/interrupt.h>


#include "BetaNTC.h"
#include "SteinhartHartNTC.h"
#include "ADConverter.h"
#include "Uart.h"


void __cxa_pure_virtual(void){};

void operator delete(void * p) // or delete(void *, std::size_t)
    {
      free(p);
    }

void adcFunc(){
	//ADConverter(Channel& channel, Frequency& freq, Reference& ref, Mode& mode);
	ADConverter adc(ADConverter::CHANNEL_0, ADConverter::F2M, ADConverter::AREF, ADConverter::FREE_RUNNING);
	Uart uart;
	sei();
	adc.run();
	volatile long int temp;
	BetaNTC sensor(10000,25l,3380);
//	SteinhartHartNTC sensor(10000,1.139506696e-03,2.333946973e-04,0.8302029848e-07);

	    while(1) {
	    	if(adc.getBuffer().available() >= 20){
	    		PORTB &= ~_BV(PORTB5);
	    		cli();
	    		temp =  sensor.getCelsiusTemperature(adc.get_conversion());
	    		sei();
	    		uart.post(temp);


	    	}


	    }
}


int main(void) {
	adcFunc();
}


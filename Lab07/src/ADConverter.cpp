#include "ADConverter.h"
#include <avr/interrupt.h>
#include <math.h>

ADConverter& ADConverter::instance = *static_cast<ADConverter*>(0);

ADConverter::~ADConverter(){

}
ADConverter::ADConverter(Channel channel, Frequency freq, Reference ref, Mode mode) : mChannel(channel) , mFreq(freq), mRef(ref), mMode(mode) {

	ADMUX = (ref << 6) | channel  ;

	if (mode != 8) {
		ADCSRA = (1 << 7) | (1 << 5) | (1 << 3) | freq;
		ADCSRB = mode;

	} else {
		ADCSRA = (1 << 7) | freq;
		ADCSRB = 0;
	}
	DDRB = 0x40;
	PORTB = 0x40;

//	enable();

	instance = *this;
}

ISR(ADC_vect){
	PORTB |= _BV(PORTB5);
	cli();
	ADConverter::getInstance().getBuffer().push(ADC);
	sei();
}
int ADConverter::RMS(const unsigned int& repeat){
	unsigned int i = 0;
	unsigned long digital_value = 0;
	unsigned long accumulated = 0, average = 0;
	while(i < repeat) {
		digital_value = this->buffer.pop();   //convert the analog-value (voltage) to digital one (0-1024)
		accumulated += digital_value*digital_value;      //accumulate all the digital-values “repeat” times
		i++;
	}
	average = accumulated / repeat;
	return sqrt(average);

}

uint16_t ADConverter::get_conversion(){
	unsigned long long int res=0,aux = 0;
	int i = 0;
	while(buffer.available()){
		i++;
		aux = this->buffer.pop();
		res += aux*aux;
	}
	return sqrt(res/i);
}

void ADConverter::run(){
	ADCSRA = ADCSRA | (1<<6);
}

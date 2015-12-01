#include "ADConverter.h"

void ADConverter::enable(){
	ADCSRA |= ( 1 << ADEN );
}
ADConverter::ADConverter(){

}
ADConverter::ADConverter(Channel channel, Frequency freq, Reference ref, Mode mode){
	ADMUX |= ( 1 << ref );
	ADMUX	|=	channel;

	enable();
}

int ADConverter::read(){
	while ((ADCSRA & _BV(ADSC)));
	return ADC;
}


void ADConverter::use_interrupts(){

}
int ADConverter::get_raw(){

}
int ADConverter::get_volt(){

}
int ADConverter::get_ref(){

}
int ADConverter::RMS(const int& repeat){
	unsigned long i = 0;
	unsigned long digital_value = 0;
	unsigned long accumulated = 0, average = 0;
	while(i < repeat) {
		digital_value = get_raw(analogPin);   //convert the analog-value (voltage) to digital one (0-1024)
		accumulated += digital_value*digital_value;      //accumulate all the digital-values “repeat” times
		i++;
	}
	average = accumulated / repeat;
	return sqrt(average);

}

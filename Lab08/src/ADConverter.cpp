#include "ADConverter.h"
#include <avr/interrupt.h>
#include <math.h>

ADConverter& ADConverter::instance = *static_cast<ADConverter*>(0);

void ADConverter::enable(){
	ADCSRA |= ( 1 << ADEN );
}
ADConverter::ADConverter(){

}
ADConverter::~ADConverter(){

}
ADConverter::ADConverter(const Channel& channel, const Frequency& freq,const Reference& ref, const Mode& mode){
	ADMUX |= ( 1 << ref );

	ADMUX |= channel;

	enable();

	instance=*this;
}

int ADConverter::get_raw(){
	while ((ADCSRA & _BV(ADSC)));
	return ADC;
}

/**
 * VectorNo. Program Address Source Interrupt Definition
 *    22           0x002A     ADC   ADC Conversion Complete
 */
void ADConverter::use_interrupts(bool enable){
	//TODO user ? operator and code the else to disable.
	if(enable)
	  ADCSRA |= 0x7A;
}
ISR(ADC_vect){
	cli();
	ADConverter::getInstance().getBuffer().push(ADC);
	sei();
}
/// TODO
int ADConverter::get_volt(){
	return 0;
	/* res = (res0*5/V0) - res0;
	 R = (R0.Vin)/Vout - R0 */
}
/// TODO
int ADConverter::get_ref(){
	return 0;
}

int ADConverter::RMS(const unsigned int& repeat){
	unsigned int i = 0;
	unsigned long digital_value = 0;
	unsigned long accumulated = 0, average = 0;
	while(i < repeat) {
		digital_value = this->get_raw();   //convert the analog-value (voltage) to digital one (0-1024)
		accumulated += digital_value*digital_value;      //accumulate all the digital-values “repeat” times
		i++;
	}
	average = accumulated / repeat;
	return sqrt(average);

}

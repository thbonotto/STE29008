#include <avr/io.h>
#include <avr/interrupt.h>

#include "NTC.h"
#include "ADConverter.h"

int main(void) {
    ADConverter adc;
    NTC sensor;
    while(1) {
    	sensor.getTemperature(adc.getBuffer().pop());
    }
    return 0;
}


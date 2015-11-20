/*
 * milli_counter.c
 *
 *  Created on: 18 de set de 2015
 *      Author: arliones.hoeller@ifsc.edu.br
 */

#include "milli_counter.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void milli_counter_start()
{
    milli_counter_ms = 0;

    TCCR0B = 0x05; //Init Timer0, normal, prescalar = 1024
    TCNT0 = 0xF0; //16 clock cycles
    TIMSK0 = 0x01; //Set TOIE bit
}

milli_counter_t milli_counter()
{
    return milli_counter_ms;
}

ISR(TIMER0_OVF_vect) {
    TCNT0 = 0xF0;
    milli_counter_ms++;
}

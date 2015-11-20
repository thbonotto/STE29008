/*
 * milli_counter.h
 *
 *  Created on: 18 de set de 2015
 *      Author: arliones.hoeller@ifsc.edu.br
 */

#ifndef MILLI_COUNTER_H_
#define MILLI_COUNTER_H_

typedef unsigned long long milli_counter_t;

milli_counter_t milli_counter_ms;

void milli_counter_start();
milli_counter_t milli_counter();

#endif /* MILLI_COUNTER_H_ */

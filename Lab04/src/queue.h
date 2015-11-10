/*
 * queue.c
 *
 *  Created on: 10 de nov de 2015
 *      Author: aluno
 */

#ifndef SRC_QUEUE_H_
#define SRC_QUEUE_H_

#define byte uint8_t
#define BUFFER_SIZE 256


#include <avr/io.h>

struct Node {
	uint8_t pos;
	byte data;
	byte * next;
	byte * prev;
};

struct Queue {
	const int size = BUFFER_SIZE;
	Node buffer [BUFFER_SIZE];
	uint8_t headPos;
	uint8_t TailPos;
};

void push();

Node pop();

#endif

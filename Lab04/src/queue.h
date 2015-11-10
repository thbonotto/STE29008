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

typedef struct Node {
	uint8_t pos;
	byte data;
	byte * next;
	byte * prev;
} Node;

typedef struct Queue {
	uint8_t size;
	Node buffer [BUFFER_SIZE];
	uint8_t headPos;
	uint8_t TailPos;
} Queue;

void push();

byte pop();

#endif

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

#include <avr/common.h>

/*typedef struct Node {
	volatile uint8_t pos;
	volatile byte data;
	volatile Node * next;
	volatile Node * prev;
} Node;
*/

typedef struct Queue {
	volatile uint8_t size;
	volatile byte buffer [BUFFER_SIZE];
	volatile uint8_t headPos;
	volatile uint8_t TailPos;
} Queue;

//TODO Implement control, circular, overflow

void push(Queue * fila, byte dado){
	if(fila->size==(BUFFER_SIZE-1))
		return; /// Buffer Overflow

	fila->buffer[fila->TailPos]=dado;

	fila->TailPos++;

	fila->size++;

}

byte pop(Queue * fila){
	if(!fila->size)
			return 0;

/*	Node * nodo = fila->buffer[fila->headPos];
	byte temp = *nodo->data;
	*nodo->data=0;
	nodo->prev->next=nodo->next;
	nodo->next->prev=nodo->prev;
*/

	byte data = fila->buffer[fila->headPos];

	fila->buffer[fila->headPos]=0;

	fila->size--;

	if(fila->size)
		fila->headPos=(fila->TailPos-1);
	else
		fila->headPos=(fila->TailPos);

	return data;
}

void init(Queue * fila){
	unsigned int i;
	fila->TailPos=0;
	fila->headPos=0;
	fila->size=0;
	for(i=0; i < BUFFER_SIZE; i++)
		fila->buffer[i]=0;
}

#endif

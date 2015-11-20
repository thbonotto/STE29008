/*
 * queue.c
 *
 *  Created on: 10 de nov de 2015
 *      Author: aluno
 */

#ifndef SRC_TX_BUFFER_H_
#define SRC_TX_BUFFER_H_

#define byte uint8_t
#define RX_BUFFER_SIZE 16

#include <stdint.h>

/*typedef struct Node {
	volatile uint8_t pos;
	volatile byte data;
	volatile Node * next;
	volatile Node * prev;
} Node;
*/

typedef struct RxBuffer {
	volatile uint8_t size;
	volatile byte buffer [RX_BUFFER_SIZE];
	volatile uint8_t headPos;
	volatile uint8_t TailPos;
} RxBuffer;

void pushRx(RxBuffer * fila, byte dado){
	if(fila->size==(RX_BUFFER_SIZE-1))
		return; /// Buffer Overflow

	fila->buffer[fila->TailPos]=dado;

	if(fila->TailPos==(RX_BUFFER_SIZE-1))
		fila->TailPos=0;
	else
	fila->TailPos++;

	fila->size++;

}

byte popRx(RxBuffer * fila){
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
		if(!fila->TailPos)
			fila->headPos=(RX_BUFFER_SIZE-1);
		else
			fila->headPos=(fila->TailPos-1);
	else
		fila->headPos=(fila->TailPos);

	return data;
}

void initRx(RxBuffer * fila){
	unsigned int i;
	fila->TailPos=0;
	fila->headPos=0;
	fila->size=0;
	for(i=0; i < RX_BUFFER_SIZE; i++)
		fila->buffer[i]=0;
}

#endif

/*
 * queue.c
 *
 *  Created on: 10 de nov de 2015
 *      Author: aluno
 */

#ifndef SRC_RX_BUFFER_H_
#define SRC_RX_BUFFER_H_

#define byte uint8_t
#define TX_BUFFER_SIZE 8

#include <stdint.h>

/*typedef struct Node {
	volatile uint8_t pos;
	volatile byte data;
	volatile Node * next;
	volatile Node * prev;
} Node;
*/

typedef struct TxBuffer {
	volatile uint8_t size;
	volatile byte buffer [TX_BUFFER_SIZE];
	volatile uint8_t headPos;
	volatile uint8_t TailPos;
} TxBuffer;

void pushTx(TxBuffer * fila, byte dado){
	if(fila->size==(TX_BUFFER_SIZE-1))
		return; /// Buffer Overflow

	fila->buffer[fila->TailPos]=dado;

	if(fila->TailPos==(TX_BUFFER_SIZE-1))
		fila->TailPos=0;
	else
	fila->TailPos++;

	fila->size++;

}

byte popTx(TxBuffer * fila){
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
			fila->headPos=(TX_BUFFER_SIZE-1);
		else
			fila->headPos=(fila->TailPos-1);
	else
		fila->headPos=(fila->TailPos);

	return data;
}

void initTx(TxBuffer * fila){
	unsigned int i;
	fila->TailPos=0;
	fila->headPos=0;
	fila->size=0;
	for(i=0; i < TX_BUFFER_SIZE; i++)
		fila->buffer[i]=0;
}

#endif

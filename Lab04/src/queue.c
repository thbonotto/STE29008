/*
 * queue.c
 *
 *  Created on: 10 de nov de 2015
 *      Author: aluno
 */

#include "queue.h"
//TODO Implement control, circular, overflow
byte pop(Queue * fila){
	Node * nodo = fila->buffer[fila->headPos];
	byte* temp = nodo->data;
	fila->headPos--;
	return *temp;
}

void push(Queue * fila, byte dado){
	fila->buffer[fila->TailPos]->data=dado;
	fila->TailPos++;
}

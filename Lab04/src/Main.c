#include "uart.h"
#include "queue.h"
// We need 2 buffers, one to store data received from serial, and another to store data that will be sent through the serial
Queue* tx_buf;
Queue* rx_buf;
static int baud_rate;
static int data_len;
static int parity;
static int stop_bits;

uint8_t data;

int rx_buffer_has_data(){
	// Todo Improve this control
	return rx_buf->headPos != rx_buf->TailPos;
}

int main(void) {
    //Configure serial to 9600 8N1
    baud_rate = 9600;
    data_len = 8;
    parity = 0;
    stop_bits = 1;
 
    //Implement loopback application - just remove older byte in the receive queue and enqueue it on the output buffer
    while(1) {  
        if(rx_buffer_has_data()){
            byte aux = pop(rx_buf);
            push(tx_buf, aux);
        }
    }
    return 0;
}

byte receive(){
		return UDR0;
}

void send(byte aux){
	UDR0 = aux;
}


// Finished sending one byte
void tx_interrupt_handler(){
    byte aux = pop(tx_buf);
    send(aux);
}
 
// Finished receiving one byte
void rx_interrupt_handler(){
    byte aux = receive();
    push(rx_buf, aux);
}

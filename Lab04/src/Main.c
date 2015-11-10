#include "uart.h"
// We need 2 buffers, one to store data received from serial, and another to store data that will be sent through the serial
byte rx_buf[BUFFER_SIZE];
byte tx_buf[BUFFER_SIZE];

static int baud_rate;
static int data_len;
static int parity;
static int stop_bits;

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
 
// Finished sending one byte
tx_interrupt_handler(){
    byte aux = pop(tx_buf);
    send(aux);
}
 
// Finished receiving one byte
rx_interrupt_handler(){
    byte aux = receive();
    push(rx_buf, aux);
}

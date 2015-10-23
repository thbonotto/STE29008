/*
 * blink.c
 *
 *  Created on: 9 de out de 2015
 *      Author: aluno
 */
 
static unsigned char *PINB  = (unsigned char *) 0x23;
static unsigned char *DDRB = (unsigned char *) 0x24; 
static unsigned char *PORTB =(unsigned char *) 0x25;  


static unsigned char *PIND  = (unsigned char *)0x29;
static unsigned char *DDRD = (unsigned char *) 0x2A; 
static unsigned char *PORTD =(unsigned char *) 0x2B; 


static unsigned char led1_msk = 0x02; // 0000 0010
static unsigned char led2_msk = 0x01; // 0000 0001

static unsigned char btn1_msk = 0x20; // 0010 0000
static unsigned char btn2_msk = 0x18; // 0001 1000

static unsigned char btn1_val = 0;
static unsigned char btn2_val = 0;

void setup() {
	*DDRD |= 0xD7; // 1101 0111
	*DDRB |= 0x03 ;// 0000 0011
}
void delay(){
	volatile unsigned long x = 0xffff;
	while(x--);
}

void switch_led1(){
	static unsigned char led1_state = 0;
	led1_state = !led1_state;
	if(led1_state)
		*PORTB |= led1_msk;
	else 
		*PORTB &= ~led1_msk;
}

void switch_led2(){
	static unsigned char led2_state = 0;
	led2_state = !led2_state;
	if(led2_state)
		*PORTB |= led2_msk;
	else 
		*PORTB &= ~led2_msk;
}

void loop() {
	btn1_val = *PIND & btn1_msk;
	btn2_val = *PIND & btn2_msk;
	
	if(btn1_val)
		switch_led1();
	if(btn2_val)
		switch_led2();
		
	delay();
}

int main() {
	setup();
	while(1)
		loop();
}

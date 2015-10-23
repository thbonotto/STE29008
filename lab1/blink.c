/*
 * blink.c
 *
 *  Created on: 9 de out de 2015
 *      Author: aluno
 */

static unsigned char *DDRD = (unsigned char *)0x2A;
static unsigned char *PORTD =(unsigned char *) 0x2B;
static unsigned char *PIND  = (unsigned char *)0x29;

static unsigned char led_msk = 0x04;
static unsigned char btn_msk = 0x08;
static unsigned char btn_val = 0;

void setup() {
	*DDRD |= 0x04;
}
void delay(){
	volatile unsigned long x = 0xffff;
	while(x--);
}
void loop() {
	btn_val = *PIND & btn_msk;
	if(btn_val)
// delay
		*PORTD |=  led_msk;
	else
		*PORTD  &=  ~led_msk;
}

int main() {
	setup();
	while(1)
		loop();
}

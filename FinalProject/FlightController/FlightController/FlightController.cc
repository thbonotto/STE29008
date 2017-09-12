#include "FlightController.h"

FlightController *FlightController::f = 0;

FlightController::FlightController(){
	DDRB |= 0x1F; // configura as saidas PORTA 0-4 como saidas
	this->channels[0].c  = 1; //aileron
	this->channels[0].name = 0;

	this->channels[1].c = 50; //elevator
	this->channels[1].name = 1;

	this->channels[2].c = 100; //throttle
	this->channels[2].name = 2;

	this->channels[3].c = 125; //rudder
	this->channels[3].name = 3;

	this->channels[4].c = 150; // canal de auto-estabilidade
	this->channels[4].name = 4;

	f = this;
	timer1(TIMER1_PRESCALER_64, 5000U, pulse);
	sei();
}

void FlightController::update(int c[5]){

	struct channel vect[5];
	for(int i=0; i<5;i++){
		vect[i] = this->channels[i];
	}
	struct channel aux;

	for(int i=0;i<5;i++){
		vect[i].c = (c[vect[i].name]*250)/100;
			}

	for(int i=4;i>=1;i--){
		for(int j=0; j<i; j++){
			if(vect[j].c>vect[j+1].c){
				aux = vect[j];
				vect[j] = vect[j+1];
				vect[j+1] = aux;
			}
		}
	}

	//desliga interrupção do timer
	TIMSK1 &= 0xDF;
	for(int i=0; i<5;i++){
		vect[i] = this->channels[i];
	}
	//liga interrupção do timer
	TIMSK1 |= 0x40;
}

void FlightController::pulse(){
	int aux = 0;
	PORTB |= 0x1F;	//setar todas portas para high

	wait0(TIMER0_PRESCALER_64,250); //1 ms

	for(int i=0;i<5;i++){
		wait0(TIMER0_PRESCALER_64,FlightController::getInstance()->getChannel(i).c);

		switch(FlightController::getInstance()->getChannel(i).name){
		case 0: PORTB &= 0xFE;
			break;
		case 1: PORTB &= 0xFD;
			break;
		case 2: PORTB &= 0xFB;
			break;
		case 3: PORTB &= 0xF7;
			break;
		case 4: PORTB &= 0xEF;
			break;
		}
	}

}

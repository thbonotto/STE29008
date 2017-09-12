#pragma once

#include "Channel.h"
#include "atmega-timers.h"
#include <avr/io.h>

using namespace std;

struct channel{
	uint8_t c;
	uint8_t name;
};

class FlightController{

public:
	FlightController();
	void update(int c[5]);
	struct channel getChannel(int i){return this->channels[i];}
	static FlightController* getInstance() {return f;}


private:
	struct channel channels[5];
	static FlightController * f;
	static void  pulse();

};

/*
 * Timer.h
 *
 *  Created on: Dec 8, 2015
 *      Author: ebroering
 */

#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

class Timer {
public:
	Timer(unsigned long freq);
	void start();
	void stop();
	void reset();
	unsigned long get_microseconds();
	static void handler();
	static Timer * getInstance(){return timer;}
	void restart() {stop();reset();start();}
	virtual ~Timer();

private:
	unsigned int freq;
	unsigned int ticks = 0;
	static Timer * timer;
	unsigned int us_ticks;



};



#endif /* SRC_TIMER_H_ */

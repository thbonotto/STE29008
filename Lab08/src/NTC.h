/*
 * NTC.h
 *
 *  Created on: 27 de nov de 2015
 *      Author: aluno
 */

#pragma once

extern "C" void __cxa_pure_virtual(void);

#include <stdlib.h>

class NTC {
public:

	virtual ~NTC();

	float getResistence(const float& Vin, const float& Vout){
		return this->mRefRes*(Vin/Vout) - this->mRefRes;
	}

	void operator delete(void * p) {
		free(p);
	}

	virtual long int getTemperature(const float& currentRes) = 0;

	inline long int getCelsiusTemperature(const float& currentRes){
		return getTemperature(currentRes) - 273.15;
	}	;
protected:
	long int mRefRes;

};


/*
 * SteinhartHartNTC.h
 *
 *  Created on: 22 de dez de 2015
 *      Author: aluno
 */

#ifndef SRC_STEINHARTHARTNTC_H_
#define SRC_STEINHARTHARTNTC_H_

#include "NTC.h"

class SteinhartHartNTC: public NTC {
public:
	SteinhartHartNTC(int refRes, float A, float B, float C);
	virtual ~SteinhartHartNTC();
	long int getTemperature(const float& currentRes);
private:
	int mA, mB, mC;
};

#endif /* SRC_STEINHARTHARTNTC_H_ */

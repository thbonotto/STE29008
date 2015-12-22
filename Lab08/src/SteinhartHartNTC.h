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
	SteinhartHartNTC(long int& refRes, long int& A, long int& B, long int& C);
	virtual ~SteinhartHartNTC();
	float getResistence(const float& Vin, const float& Vout);
	long int getTemperature(const float& currentRes);
private:
	long int mRefRes, mA, mB, mC;
};

#endif /* SRC_STEINHARTHARTNTC_H_ */

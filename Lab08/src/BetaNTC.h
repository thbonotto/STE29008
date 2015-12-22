/*
 * BetaNTC.h
 *
 *  Created on: 22 de dez de 2015
 *      Author: aluno
 */

#ifndef SRC_BETANTC_H_
#define SRC_BETANTC_H_

#include "NTC.h"

class BetaNTC: public NTC {
public:
	BetaNTC(long int& refRes, long int& tempRes, long int& beta);
	virtual ~BetaNTC();
	float getResistence(const float& Vin, const float& Vout);
	long int getTemperature(const float& currentRes);
private:
	long int mRefRes, TempRes, mBeta;
};

#endif /* SRC_BETANTC_H_ */

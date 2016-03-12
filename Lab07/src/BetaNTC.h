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
	BetaNTC(

	);
	virtual ~BetaNTC();
	long int getTemperature(const float& currentRes);
private:
	int mTempRes, mBeta;
};

#endif /* SRC_BETANTC_H_ */

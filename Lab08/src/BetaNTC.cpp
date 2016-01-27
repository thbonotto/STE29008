/*
 * BetaNTC.cpp
 *
 *  Created on: 22 de dez de 2015
 *      Author: aluno
 */

#include "BetaNTC.h"
#include <math.h>

BetaNTC::BetaNTC(long int& refRes, long int& tempRes, long int& beta) :  mTempRes(tempRes), mBeta(beta) {
	this->mRefRes=refRes;

}

BetaNTC::~BetaNTC() {

}


long int BetaNTC::getTemperature(const float& resistence){

	long int T,inverseT;
	inverseT = 1/this->mTempRes + (1/this->mBeta)*log(resistence/this->mRefRes);
	T = 1/inverseT;

	return T;
}

/*
 * BetaNTC.cpp
 *
 *  Created on: 22 de dez de 2015
 *      Author: aluno
 */

#include "BetaNTC.h"
#include <math.h>

BetaNTC::BetaNTC(long int& refRes, long int& tempRes, long int& beta) {
	// TODO Auto-generated constructor stub

}

BetaNTC::~BetaNTC() {
	// TODO Auto-generated destructor stub
}

float BetaNTC::getResistence(const float& Vin, const float& Vout){
	float tempRes;
	//TODO Calculations
	return tempRes;
}

long int BetaNTC::getTemperature(const float& resistence){

	long int T,inverseT;
	inverseT = 1/this->TempRes + (1/this->mBeta)*log(resistence/this->mRefRes);
	T = 1/inverseT;

	return T;
}

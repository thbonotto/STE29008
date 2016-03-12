/*
 * SteinhartHartNTC.cpp
 *
 *  Created on: 22 de dez de 2015
 *      Author: aluno
 */

#include "SteinhartHartNTC.h"
#include <math.h>

SteinhartHartNTC::SteinhartHartNTC(int refRes, float A, float B, float C) : mA(A), mB(B), mC(C) {
	this->mRefRes=refRes;
}

SteinhartHartNTC::~SteinhartHartNTC() {
	// TODO Auto-generated destructor stub
}

//TODO
long int SteinhartHartNTC::getTemperature(const float& resistence) {

	long int TempTemp;
	TempTemp = this->mA + (this->mB*log(resistence)) + this->mC*(pow(log(resistence),3));
	return 1/TempTemp;
}

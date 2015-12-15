/*
 * NTC.cpp
 *
 *  Created on: 27 de nov de 2015
 *      Author: aluno
 */

#include "NTC.h"

NTC::NTC(long int& refRes, long int& beta) : _mode{Beta}, mRefRes{refRes} , mAorBeta{beta} {

}

NTC::NTC(long int& A, long int& B, long int& C, long int& refRes)  : _mode{SteinhartHart},  mRefRes{refRes} , mAorBeta{A}, mB{B}, mC{C}{

}

NTC::~NTC(){

}

long int NTC::getTemperatureBeta(){

	long int T;
	1/T = 1/T0 + (1/b)
	T = this->mAorBeta/lnDivisor() ;
		return T;
}

long int NTC::getTemperatureSteinhartHart(){

		return 25;
}

long int NTC::getTemperature(const long int& resistence){
	return (this->_mode == Beta) ? getTemperatureBeta() : getTemperatureSteinhartHart();
}




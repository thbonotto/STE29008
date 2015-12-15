/*
 * NTC.cpp
 *
 *  Created on: 27 de nov de 2015
 *      Author: aluno
 */

#include "NTC.h"

NTC::NTC(long int& refRes, long int& tempRes, long int& beta) : _mode{Beta}, mRefRes{refRes}, mAorTempRes{tempRes}, mBorBeta{beta} {

}

NTC::NTC(long int& refRes, long int& A, long int& B, long int& C)  : _mode{SteinhartHart},  mRefRes{refRes} , mAorTempRes{A}, mBorBeta{B}, mC{C}{

}

NTC::~NTC(){

}
//TODO
long int NTC::lnDivisor(const long int& num, const long int& dem){
	return 1;
}

float getResistence(const float& Vin, const float& Vout){
	float tempRes;
	//TODO Calculations
	return tempRes;
}

long int NTC::getTemperatureBeta(const float& resistence){

	long int T,inverseT;
	inverseT = 1/this->mAorTempRes + (1/this->mBorBeta)*lnDivisor(resistence,this->mRefRes);
	T = 1/inverseT;

	return T;
}
//TODO
long int NTC::getTemperatureSteinhartHart(const float& resistence){

		return 25;
}

long int NTC::getTemperature(const float& resistence){
	return (this->_mode == Beta) ? getTemperatureBeta(resistence) : getTemperatureSteinhartHart(resistence);
}




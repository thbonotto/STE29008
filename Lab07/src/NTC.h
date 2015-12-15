/*
 * NTC.h
 *
 *  Created on: 27 de nov de 2015
 *      Author: aluno
 */

#ifndef SRC_NTC_H_
#define SRC_NTC_H_

class NTC {
public:
	/**
	 *
	 */
	NTC(long int& refRes, long int& tempRes, long int& beta);
	/**
	 *
	 */
	NTC(long int& refRes, long int& A, long int& B, long int& C);

	virtual ~NTC();

	float getResistence(const float& Vin, const float& Vout);

	long int getTemperature(const float& currentRes);
private:
	enum Type {
		Beta,
		SteinhartHart
	};

	long int NTC::lnDivisor(const long int& num, const long int& dem);

	long int NTC::getTemperatureBeta(const float& resistence);

	long int NTC::getTemperatureSteinhartHart(const float& resistence);

	Type _mode;

	long int mRefRes, mAorTempRes, mBorBeta, mC{0};


};

#endif /* SRC_NTC_H_ */

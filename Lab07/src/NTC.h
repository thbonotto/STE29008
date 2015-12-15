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
	NTC(long int& beta, long int& refRes);
	/**
	 *
	 */
	NTC(long int& A, long int& B, long int& C, long int& refRes);

	virtual ~NTC();
	long int getTemperature(const long int& currentRes);
private:
	enum Type {
		Beta,
		SteinhartHart
	};

	Type _mode;

	long int NTC::getTemperatureBeta();

	long int NTC::getTemperatureSteinhartHart();

	long int mRefRes, mAorBeta, mB{0}, mC{0};
};

#endif /* SRC_NTC_H_ */

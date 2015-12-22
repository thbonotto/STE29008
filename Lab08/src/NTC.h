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
	NTC();

	virtual ~NTC();

	virtual float getResistence(const float& Vin, const float& Vout) = 0;

	virtual long int getTemperature(const float& currentRes) = 0;
};

#endif /* SRC_NTC_H_ */

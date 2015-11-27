/*
 * NTC.cpp
 *
 *  Created on: 27 de nov de 2015
 *      Author: aluno
 */

#include "NTC.h"

NTC::NTC() {
	// TODO Auto-generated constructor stub

}

NTC::~NTC() {
	// TODO Auto-generated destructor stub
}

void NTC::getTemperature(){
  //  res = (res0*5/V0) - res0;
    /* R = (R0.Vin)/Vout - R0 */

  //  TK =  1/T0 + (1/beta)*log(res/res0);
 //   TK = 1/TK;
    /* 1/T = 1/T0 + 1/B x ln(R/R0) */
    /*TK é a temperatura em kelvins, para adquirí-la em Celcius ou Fahrenheit e preciso realizar as conversões:
    TC = (TK - 273.15) e  TF = (TC*5/9 + 32)*/
}

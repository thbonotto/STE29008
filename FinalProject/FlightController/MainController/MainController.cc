#include "MainController.h"
#include "../FlightController/FlightController.h"
#include "DataBase.h"
#include "../GPS.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <util/delay.h>
MainController::MainController(FlightController* fc, NMEA* gps, Communicator * com,
		DataBase * db, State FirstState) :
		fc(fc) , gps(gps), com(com), db(db), mState(FirstState) {
}

MainController::~MainController() {

}
void MainController::run() {
	static int valores[5];
	valores[0]=0;
	valores[1]=0;
	valores[2]=0;
	valores[3]=0;
	valores[4]=0;

	float angle,distance;
	static int missionPos = 0;
	switch (this->mState) {
	case Standby:
		/**
		 * time[0] = hora, time[1] =  minuto, time[2] = segundos,
		 * time[3] = dia, time[4] = mes, time[5] = ano.
		 */
		if (mCurrentMission == NULL)
			mState = LoadMission;
		else if (com->dataAvaliable()) {
			mState = ReadFromNetwork;
		}
		else  {
			if (gps->getHour() >= mCurrentMission->time[0]
					&& gps->getMinute() >= mCurrentMission->time[1]
					&& gps->getSecond() >= mCurrentMission->time[2]
					&& gps->getDay() == mCurrentMission->time[3]
					&& gps->getMonth() >= mCurrentMission->time[4]
					&& gps->getYear() >= mCurrentMission->time[5])
				mState = TakeOff;
		}
		break;
	case ReadFromNetwork:
		while (com->dataAvaliable()) {
			mCurrentMission = (Mission*) malloc(sizeof(Mission));
			uint8_t * missionPtr = (uint8_t *) mCurrentMission;
			uint8_t byte = com->getByte();
			memcpy((void*) missionPtr, (void*) &byte, sizeof(uint8_t));
			missionPtr++;
		}
		break;
	case StoreMission:
		db->saveMission(mCurrentMission);
		free(mCurrentMission);
		mCurrentMission = NULL;
		break;
	case LoadMission:
		mCurrentMission = db->loadMission();
		mState = Standby;
		break;
	case TakeOff:
		//TODO Trouble using timer?
		_delay_ms(2000);
		valores[0]=125;
			fc->update(valores);
		mState = ReadFromSensors;
		break;
	case ReadFromSensors:
		valores[0] = fc->getChannel(0).c;
		valores[1] = fc->getChannel(1).c;
		valores[2] = fc->getChannel(2).c;
		valores[3] = fc->getChannel(3).c;
		mState = CalculateVector;
		break;
	case CalculateVector:
		if(mCurrentMission->Action[missionPos]==TestMission)
			mState = doTestMission;
		angle = gps->gprmc_course_to(mCurrentMission->Latitude[missionPos],
				mCurrentMission->Longitude[missionPos]);
		distance = gps->gprmc_distance_to(mCurrentMission->Latitude[missionPos],
				mCurrentMission->Longitude[missionPos],1);
		/**
		 * If angle is good move to location;
		 * Else correct angle
		 */
		if (angle >= -0.5 && angle <= 0.5 ) {
			if(distance <= 0.1){
				valores[2]=50;
				mState = PointReached;
			} else {
				valores[2]=45;
				mState = UpdateOutputs;
			}
		} else {
			if (angle > 0) {
				valores[1] = 120;
			} else {
				valores[1] = 130;
			}
			mState = UpdateOutputs;
		}
		break;
	case UpdateOutputs:
		fc->update(valores);
		mState = CalculateVector;
		break;
	case PointReached:
		if (mCurrentMission->Action[missionPos] == LandDrone) {
			mState = Land;
		} else if (mCurrentMission->Action[missionPos] == Up) {
			valores[0] = 130;
		} else if (mCurrentMission->Action[missionPos] == Down) {
			valores[0] = 120;
		}
		missionPos++;
		valores[0]=125;
		valores[1]=125;
		valores[2]=125;
		valores[3]=125;
		valores[4]=250;
		mState = UpdateOutputs;
		break;
	case Land:
		for (int power = 125; power > 0; power--) {
			valores[0]=power;
			fc->update(valores);
			//TODO Trouble using timer?
			_delay_ms(2000);
		}
		if(mCurrentMission->Action[missionPos + 1]==LandDrone || missionPos >= MAX_MISSION_SIZE) {
			missionPos = 0;
			free(mCurrentMission);
			mCurrentMission = NULL;
			mState = Standby;
		} else {
			missionPos++;
			mState = TakeOff;
		}
		break;
	case doTestMission:
		_delay_ms(5000);
		volatile unsigned long x = 0xffff;
		//ARM
		while (x--) {
			valores[3] = 250;
			// Take off
			fc->update(valores);
		}
		x = 0xffff;
		valores[3] = 125;

		while(x--){
		valores[0]=250;
		// Take off
		fc->update(valores);
		}
		x = 0xffff;
		valores[0]=125;


		// Walk to front
		valores[2]=135;
		while(x--){
		fc->update(valores);
		//_delay_ms(2000);
		}
		x = 0xffff;
		valores[2]=125;

		//  Turn right?
		valores[1]=130;
		while(x--){
		fc->update(valores);
		}
		x = 0xffff;
		//_delay_ms(2000);

		//  Turn left?
		valores[1] = 130;
		while(x--){
		fc->update(valores);
		}
		x = 0xffff;
		valores[1] = 125;

		// Land
		while (x--) {
			valores[0]--;
			fc->update(valores);
		}
		x = 0xffff;

		_delay_ms(10000);
		break;
	}
}

int main() {
	FlightController fc;
//	NMEA gps(GPRMC);
//	Communicator com;
//	DataBase db;
	MainController app(&fc, 0, 0, 0);
	while(1)
		app.run();
	return 0;

}

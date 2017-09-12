/*
 * MainController.h
 *
 *  Created on: Feb 23, 2016
 *      Author: thiago.b
 */

#pragma once
#include "../Communicator.h"
#include "../FlightController/FlightController.h"
#include "../GPS.h"
#include "DataBase.h"
#include "Mission.h"

class MainController {
public:
	enum State {
		Standby,
		ReadFromNetwork,
		StoreMission,
		LoadMission,
		TakeOff,
		ReadFromSensors,
		CalculateVector,
		UpdateOutputs,
		PointReached,
		Land,
		doTestMission
	};
	MainController(FlightController* fc,
	NMEA* gps,
	Communicator * com,
	DataBase * db,
	State FirstState=doTestMission);

	virtual ~MainController();
	void run();
private:
	FlightController* fc;
	NMEA* gps;
	Communicator * com;
	DataBase * db;
	State mState;
	Mission * mCurrentMission;
};

/* FLIGHTCONTROLLER_MAINCONTROLLER_H_ */

#pragma once
#include "Mission.h"
#include <avr/io.h>
#define TESTING_MISSION
class DataBase {
public:
	DataBase();
	virtual ~DataBase();
	void saveMission(Mission* mission);
#ifndef TESTING_MISSION
	Mission* loadMission();
#else
	Mission* loadMission(){
			return &testMission;
	}
	private:
	Mission testMission;
#endif
	private:
	Mission* eempromPosition;
};

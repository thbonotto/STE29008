#include "DataBase.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <avr/eeprom.h>

DataBase::DataBase() :
		eempromPosition(0) {
#ifdef TESTING_MISSION
	testMission.Latitude[0] = 0.0;
	testMission.Longitude[0] = 0.0;
	testMission.Action[0] = TestMission;
#endif
}

DataBase::~DataBase() {

}

void DataBase::saveMission(Mission* mission) {
	eeprom_write_block((void*) mission, eempromPosition, sizeof(Mission));
	eempromPosition--;
}
#ifndef TESTING_MISSION
Mission* DataBase::loadMission() {
	Mission* newMission = (Mission*) malloc(sizeof(Mission));
	eeprom_read_block((void*) newMission, eempromPosition, sizeof(Mission));
	eempromPosition--;
	return newMission;
}
#endif

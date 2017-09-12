/*
 * Mission.h
 *
 *  Created on: Mar 11, 2016
 *      Author: thiago.b
 */

#pragma once 
#define MAX_MISSION_SIZE 10

enum Actions {
	TakePicture,
	ReadTemperature,
	LandDrone,
	TestMission,
	Up,
	Down,
	Turn,
	Front,
	Back
};
struct Mission {
    /**
     * time[0] = hora, time[1] =  minuto, time[2] = segundos,
     * time[3] = dia, time[4] = mes, time[5] = ano.
     */
    int time[6];
    /**
     * Example:
     * Actions[0]= <[-27.6078233,-48.6322714],0>
     * Actions[1]= <[-27.608258,-48.6340522],1>
     * Actions[2]= <[-27.607818,-48.6341352],3>
     */
    float Latitude[MAX_MISSION_SIZE];
    float Longitude[MAX_MISSION_SIZE];
    float Action[MAX_MISSION_SIZE];
};

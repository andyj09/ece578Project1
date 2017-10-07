//============================================================================
// Name        : hello.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <cmath>
#include "TimelineSlots.hpp"
#include <random>
#include <deque>
#include "Station.hpp"
#include "utilities.hpp"

using namespace std;
struct debugInfo_t debugInfo;

int main(int argc, const char *argv[])
{
	TimelineSlots &tmLineInst = TimelineSlots::getInstance();

	// read command line arguments
	if (!getCLIArgs(argc, argv, debugInfo))
	{
		return 0;
	}

	// read config file
	if (tmLineInst.readConfig(debugInfo.config))
	{
		return 0;
	}
	
	// compute dynamic timeline parameters
	tmLineInst.computeSlotUnits();
   
	// create All required stations
	Station A(COLLISION_DMN::ONE,TYPEOFS::SENDER,"A","B");
	Station B(COLLISION_DMN::ONE,TYPEOFS::RECEIVER,"B","");
	Station C(COLLISION_DMN::ONE,TYPEOFS::SENDER,"C","D");
	Station D(COLLISION_DMN::ONE,TYPEOFS::RECEIVER,"D","");

	// add all station to a list
	std::vector<Station> vectStations {A,B,C,D};
	tmLineInst.setStations(vectStations);

	// populate arrival times
	tmLineInst.addProbOfArrival();

	// set the starting state
	Status::State curStatus = Status::State::DIFS;
	tmLineInst.setCurrentTimeSlot(0);

	/*
		All simulation parameters have been setup by this point.
		This is main simulation loop. Simply loop over all possible slots and
		update the simulation world on every slot.
	*/
	int currentSlot = tmLineInst.getCurrentTimeSlot();
	int counter = 0;
	while (currentSlot < tmLineInst.getSlot().totalSim)
	{
		tmLineInst.updateEachStation();
	}

//	curStatus = tmLineInst.iterateToState(curStatus,0);

//	if(curStatus == Status::State::ENDOFSIM)
//	{
//		printf("Terminated at i='%d'\n",tmLineInst.getCurrentTimeSlot());
//	}

	return 0;

}

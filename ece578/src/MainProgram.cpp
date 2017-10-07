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
// get base random alias which is auto seeded and has static API and internal state
#include "include/effolkronium/random.hpp" // https://github.com/effolkronium/random
using Random = effolkronium::random_static;
struct debugInfo_t debugInfo;

int main(int argc, const char *argv[])
{
	cout << "HLVL: Start of Main " << endl;
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
	
	tmLineInst.computeSlotUnits();

	Station A(COLLISION_DMN::ONE,TYPEOFS::SENDER,"A","B");
	Station B(COLLISION_DMN::ONE,TYPEOFS::RECEIVER,"B","");
	Station C(COLLISION_DMN::ONE,TYPEOFS::SENDER,"C","D");
	Station D(COLLISION_DMN::ONE,TYPEOFS::RECEIVER,"D","");

	std::vector<Station> vectStations {A,B,C,D};
	tmLineInst.setStations(vectStations);


	Status::State curStatus = Status::State::DIFS;
	tmLineInst.setCurrentTimeSlot(0);
	tmLineInst.addProbOfArrival();
	curStatus = tmLineInst.iterateToState(curStatus,0);

	if(curStatus == Status::State::ENDOFSIM)
	{
		printf("Terminated at i='%d'\n",tmLineInst.getCurrentTimeSlot());
	}

	return 0;

}

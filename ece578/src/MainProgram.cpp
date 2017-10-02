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

using namespace std;
// get base random alias which is auto seeded and has static API and internal state
#include "include/effolkronium/random.hpp" // https://github.com/effolkronium/random
using Random = effolkronium::random_static;

int main()
{
	cout << "HLVL: Start of Main " << endl;
	TimelineSlots &tmLineInst = TimelineSlots::getInstance();


	// Delete This
	double deletemeLater  = 0.000020 * 500;
	// TODO: read parameters from .ini/.conf file
	tmLineInst.setDifsDuration(0.000040); 	// DIFS Duration 40 uS ~= 2 Slots
	tmLineInst.setSifsDuration(0.000010); 	// SIFS Duration 10 uS ~= 1 Slot
	tmLineInst.setSlotDuration(0.000020);		// Slot Duration 20 uS
	tmLineInst.setTotalSimTime(deletemeLater); 			// Simulation time 10 S  ~= 500,000 Slots
	tmLineInst.setMediumBandWidth(6000000); 	// Transmission rate 6 Mbps
	tmLineInst.setFrameXmitSzBits(1500*8);   	// It takes 250 uS to xmit a frame  ~= 13 Slots
	tmLineInst.setAckRtsCtsSizeBits(8*30); 	// ACK, RTS, CTS size = 30 bytes ~= 5 uS ~= 1 Slot
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

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
#include "StationClass.hpp"
#include "TimelineSlots.hpp"
#include <random>
#include <deque>

using namespace std;
// get base random alias which is auto seeded and has static API and internal state
#include "include/effolkronium/random.hpp" // https://github.com/effolkronium/random
using Random = effolkronium::random_static;

int main()
{
	cout << "HLVL: Start of Main " << endl;
	TimelineSlots &tmLineInst = TimelineSlots::getInstance();

	// TODO: read parameters from .ini/.conf file
	tmLineInst.setDifsDuration(0.000040); 	// DIFS Duration 40 uS ~= 2 Slots
	tmLineInst.setSifsDuration(0.000010); 	// SIFS Duration 10 uS ~= 1 Slot
	tmLineInst.setSlotDuration(0.000020);		// Slot Duration 20 uS
	tmLineInst.setTotalSimTime(10); 			// Simulation time 10 S  ~= 500,000 Slots
	tmLineInst.setMediumBandWidth(6000000); 	// Transmission rate 6 Mbps
	tmLineInst.setFrameXmitTime(0.000250);   	// It takes 250 uS to xmit a frame  ~= 13 Slots
	tmLineInst.setAckRtcCtsSizeBits(8*30); 	// ACK, RTS, CTS size = 30 bytes ~= 5 uS ~= 1 Slot


	StationClass proto;

	for(int i=0; i < 50; i++)
	{
		proto.chooseBackOffTime();
		cout << "Random Value select = "  << proto.getBOCountDown() << endl;
		if(!(i%10))
		{
			proto.increaseBOSelectRange();
		}
	}
	///////////////////////////////////////
	std::deque<int> framesToXmit;
	for(int i=0; i<50000;i++)
	{
		if(Random::get<bool>(0.006)) // true with 0.6% probability aka '300';
		{
			framesToXmit.push_back(i);
			cout << "Added to queue in slot i=" << i << endl;
		}
	}

	cout << "HLVL: packjets to transmit " << framesToXmit.size() << endl;
	return 0;

}

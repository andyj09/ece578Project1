/*
 * TimeSlots.hpp
 *
 *  Created on: Sep 28, 2017
 *      Author: abc
 */

#ifndef TIMELINESLOTS_HPP_
#define TIMELINESLOTS_HPP_

#include <limits>
#include <vector>
#include "Station.hpp"
#include <map>


struct Slotted
{
	int sifsDuration; 	// In Seconds
	int difsDuration; 	// In Seconds
	int totalSim; 		// Total Simulation time
	int frameXmitt; 	// Time to xmit a package/frame
	int ackRtsCtsSize;
};


namespace Status
{
	enum State
	{
		IDLE,
		DIFS,
		BOPERIOD,
		SIFS,
		DATA,
		RTS,
		CTS,
		ACK,
		ENDOFSIM,
		NUMOFSTATUS
	};
};


class TimelineSlots
{
public:
	  static TimelineSlots& getInstance(void)
	{
		static TimelineSlots instance; // Guaranteed to be destroyed.
		return instance;
	}

	bool readConfig(std::string fname);
	int increaseTimeSlot(void);


	// C++ 11
	TimelineSlots(TimelineSlots const &) = delete; 		// copy ctor
	void operator=(TimelineSlots const &) = delete;

	int getCurrentTimeSlot() const;
	void setCurrentTimeSlot(int currentTimeSlot);
	double getDifsDuration() const;
	void setDifsDuration(double difsDuration);
	double getFrameBits() const;
	void setFrameBits(double frameBits);
	double getMediumBandWidth() const;
	void setMediumBandWidth(double mediumBandWidth);
	double getSifsDuration() const;
	void setSifsDuration(double sifsDuration);
	double getSlotDuration() const;
	void setSlotDuration(double slotDuration);
	double getNetworkBandWidth() const;
	void setNetworkBandWidth(double networkBandWidth);
	double getTotalSimTime() const;
	void setTotalSimTime(double totalSimTime);
	double getFrameXmitSzBits() const;
	void setFrameXmitSzBits(int frameXmitBits);
	int getAckRtsCtsSizeBits() const;
	void setAckRtsCtsSizeBits(int ackRtsCtsSizeBits);
	void setNextState(Status::State e);
	Status::State getCurrentState() const;
	int setCurrentState(const Status::State currentState);
	const Slotted& getSlot() const;
	void setSlot(const Slotted& slot);
	const std::vector<Station>& getStations() const;
	void setStations(const std::vector<Station>& stations);

	void computeSlotUnits(void);
	Status::State iterateToState(const Status::State e, const int &i);
	void doCommonStuff(void);
	bool doBackOffPeriodStuff(void);
	void addProbOfArrival(void);
	bool readArrivalTimesFromFile(std::vector<double> &outVec, std::string);
	void generateTrueArrivalSlots(Station &station);
	void updateEachStation();
	void checkIdleState(Station &station);
	void checkDIFSState(Station &station);
	void checkBackOffState(Station &station);
	void checkXmitDataState(Station &station);
	void checkSIFSState(Station &station);
	void checkACKStation(Station &station);
	

	// assignment ctor
	// Note: Scott Meyers mentions in his Effective Modern
	//       C++ book, that deleted functions should generally
	//       be public as it results in better error messages
	//       due to the compilers behavior to check accessibility
	//       before deleted status
private:
	TimelineSlots():
		slotDuration(std::numeric_limits<double>::min()),
		sifsDuration(std::numeric_limits<double>::min()),
		difsDuration(std::numeric_limits<double>::min()),
		networkBandWidth(std::numeric_limits<double>::min()),
		frameBits(std::numeric_limits<double>::min()),
		totalSimTime(std::numeric_limits<double>::min()),
		frameXmitSzBits(std::numeric_limits<int>::min()),
		mCurrentTimeSlot(0),
		ackRtsCtsSizeBits(std::numeric_limits<int>::min()),
		currentState(Status::DIFS),
		numStationsToXmit(0)
	{

	}
	//~TimelineSlots();// dtor
	double slotDuration; 	// In Seconds
	double sifsDuration; 	// In Seconds
	double difsDuration; 	// In Seconds
	double networkBandWidth;	// bits per Second
	double frameBits;		// number of bits in a frame
	double totalSimTime; // Total Simulation time
	int frameXmitSzBits; // Time to transmist a package/frame
	int mCurrentTimeSlot;
	int ackRtsCtsSizeBits;
	Status::State currentState;
	Slotted slot;
	std::vector<Station> vStations;
	std::vector<Station *> vXmits;
	std::map<std::string, int> lambdaMap;
	int numStationsToXmit;
	TxData lastXmit;
	std::map<std::string,COLLISION_DMN> mMapStations;
};



#endif /* TIMELINESLOTS_HPP_ */

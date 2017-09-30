/*
 * TimeSlots.hpp
 *
 *  Created on: Sep 28, 2017
 *      Author: abc
 */

#ifndef TIMELINESLOTS_HPP_
#define TIMELINESLOTS_HPP_

#include <limits>

struct Slotted
{
	int sifsDuration; 	// In Seconds
	int difsDuration; 	// In Seconds
	int totalSim; // Total Simulation time
	int frameXmitt; // Time to transmist a package/frame
	int ackRtcCtsSize;
};

class TimelineSlots
{
public:
	  static TimelineSlots& getInstance(void)
	{
		static TimelineSlots instance; // Guaranteed to be destroyed.
		return instance;
	}

	int increaseTimeSlot(const int &inc);


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
	double getFrameXmitTime() const;
	void setFrameXmitTime(double frameXmitTime);
	int getAckRtcCtsSizeBits() const;
	void setAckRtcCtsSizeBits(int ackRtcCtsSizeBits);
	void computeSlotUnits(void);

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
		frameXmitTime(std::numeric_limits<double>::min()),
		currentTimeSlot(0),
		ackRtcCtsSizeBits(std::numeric_limits<int>::min())
	{

	}
	//~TimelineSlots();// dtor
	double slotDuration; 	// In Seconds
	double sifsDuration; 	// In Seconds
	double difsDuration; 	// In Seconds
	double networkBandWidth;	// bits per Second
	double frameBits;		// number of bits in a frame
	double totalSimTime; // Total Simulation time
	double frameXmitTime; // Time to transmist a package/frame
	int currentTimeSlot;
	int ackRtcCtsSizeBits;
	Slotted slot;
	// It takes 250 uS to xmit a frame  ~= 13 Slots
	// Slot Duration 20 uS
	// SIFS Duration 10 uS ~= 1 Slot
	// DIFS Duration 40 uS ~= 2 Slots
	// Simulation time 10 S  ~= 500,000 Slots
	// ACK, RTS, CTS size = 30 bytes ~= 5 uS ~= 1 Slot
	// Transmission rate 6 Mbps
};



#endif /* TIMELINESLOTS_HPP_ */

/*
 * TimelineSlots.cpp
 *
 *  Created on: Sep 28, 2017
 *      Author: abc
 */
#include "TimelineSlots.hpp"
#include <iostream>

// Increase the time Slot counter and return the current time slot
int TimelineSlots::increaseTimeSlot(const int& inc) {
	currentTimeSlot = inc;
	return(currentTimeSlot);
}

int TimelineSlots::getCurrentTimeSlot() const {
	return currentTimeSlot;
}


double TimelineSlots::getDifsDuration() const {
	return difsDuration;
}

void TimelineSlots::setDifsDuration(double difsDuration) {
	if(this->difsDuration == std::numeric_limits<double>::min())
	{
		this->difsDuration = difsDuration;
	}
}

double TimelineSlots::getFrameBits() const {
	return frameBits;
}

void TimelineSlots::setFrameBits(double frameBits) {
	if(this->frameBits == std::numeric_limits<double>::min())
	{
		this->frameBits = frameBits;
	}
}

double TimelineSlots::getMediumBandWidth() const {
	return networkBandWidth;
}

void TimelineSlots::setMediumBandWidth(double mediumBandWidth) {
	if(this->networkBandWidth == std::numeric_limits<double>::min())
	{
		this->networkBandWidth = mediumBandWidth;

	}
}

double TimelineSlots::getSifsDuration() const {
	return sifsDuration;
}

void TimelineSlots::setSifsDuration(double sifsDuration) {
	if(this->sifsDuration == std::numeric_limits<double>::min())
	{
		this->sifsDuration = sifsDuration;

	}
}

double TimelineSlots::getSlotDuration() const {
	return slotDuration;
}

void TimelineSlots::setSlotDuration(double slotDuration) {
	if(this->slotDuration == std::numeric_limits<double>::min())
	{
		this->slotDuration = slotDuration;

	}
}

double TimelineSlots::getNetworkBandWidth() const {
	return networkBandWidth;
}

void TimelineSlots::setNetworkBandWidth(double networkBandWidth) {
	if(this->networkBandWidth == std::numeric_limits<double>::min() ){
		this->networkBandWidth = networkBandWidth;
	}
}

double TimelineSlots::getTotalSimTime() const {
	return totalSimTime;
}

void TimelineSlots::setTotalSimTime(double totalSimTime) {
	if(this->totalSimTime == std::numeric_limits<double>::min())
	{
		this->totalSimTime = totalSimTime;
	}
}

double TimelineSlots::getFrameXmitTime() const {
	return frameXmitTime;
}

void TimelineSlots::setFrameXmitTime(double frameXmitTime) {
	if(this->frameXmitTime == std::numeric_limits<double>::min())
	{
		this->frameXmitTime = frameXmitTime;
	}
}

int TimelineSlots::getAckRtcCtsSizeBits() const {
	return ackRtcCtsSizeBits;
}

void TimelineSlots::setAckRtcCtsSizeBits(int ackRtcCtsSizeBits) {
	if(this->ackRtcCtsSizeBits == std::numeric_limits<int>::min())
	{
		this->ackRtcCtsSizeBits = ackRtcCtsSizeBits;
	}
}

void TimelineSlots::computeSlotUnits(void) {
	if(true)
	{

	}
	else
	{
		std::cout << "HLVL: needed units have not been defined" << std::endl;
	}
}

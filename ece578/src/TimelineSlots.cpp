/*
 * TimelineSlots.cpp
 *
 *  Created on: Sep 28, 2017
 *      Author: abc
 */
#include "TimelineSlots.hpp"
#include <iostream>
#include <cmath>

#include "include/effolkronium/random.hpp" // https://github.com/effolkronium/random
using Random = effolkronium::random_static;

using namespace std;
typedef std::vector<Station>::iterator VSI;


// Increase the time Slot counter and return the current time slot
int TimelineSlots::increaseTimeSlot(void) {
	mCurrentTimeSlot++;
	addProbOfArrival();
	return(mCurrentTimeSlot);
}

int TimelineSlots::getCurrentTimeSlot() const {
	return mCurrentTimeSlot;
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

double TimelineSlots::getFrameXmitSzBits() const {
	return frameXmitSzBits;
}

void TimelineSlots::setFrameXmitSzBits(int frameXmitBits) {
	if(this->frameXmitSzBits == std::numeric_limits<int>::min())
	{
		this->frameXmitSzBits = frameXmitBits;
	}
}

int TimelineSlots::getAckRtsCtsSizeBits() const {
	return ackRtsCtsSizeBits;
}

void TimelineSlots::setAckRtsCtsSizeBits(int ackRtcCtsSizeBits) {
	if(this->ackRtsCtsSizeBits == std::numeric_limits<int>::min())
	{
		this->ackRtsCtsSizeBits = ackRtcCtsSizeBits;
	}
}

void TimelineSlots::computeSlotUnits(void) {
	double minDobule = std::numeric_limits<double>::min();
	if(	this->difsDuration 		!= minDobule &&
		this->sifsDuration 		!= minDobule &&
		this->slotDuration		!= minDobule &&
		this->totalSimTime		!= minDobule &&
		this->networkBandWidth  != minDobule &&
		this->frameXmitSzBits   !=  std::numeric_limits<int>::min() &&
		this->ackRtsCtsSizeBits != std::numeric_limits<int>::min())
	{
		// We have all the information that we need to calculate slots
		this->slot.totalSim 		= std::ceil(this->totalSimTime/this->slotDuration);
		this->slot.ackRtsCtsSize 	= std::ceil(( this->ackRtsCtsSizeBits / this->networkBandWidth ) / this->slotDuration);
		this->slot.difsDuration		= std::ceil(this->difsDuration/this->slotDuration);
		this->slot.frameXmitt       = std::ceil(this->frameXmitSzBits/this->networkBandWidth / this->slotDuration);
		this->slot.sifsDuration     = std::ceil(this->sifsDuration / this-> slotDuration);


		std::cout	<< " HLVL this->slot.totalSim " 		<< this->slot.totalSim
				  << "\n HLVL this->slot.ackRtcCtsSize " 	<< this->slot.ackRtsCtsSize
				  << "\n HLVL this->slot.difsDuration " 	<< this->slot.difsDuration
				  << "\n HLVL this->slot.frameXmitt " 		<< this->slot.frameXmitt
				  << "\n HLVL this->slot.sifsDuration " 	<< this->slot.sifsDuration << std::endl;
	}
	else
	{
		std::cout << "HLVL: needed units have not been defined" << std::endl;
	}
}

Status::State TimelineSlots::getCurrentState() const {
	return currentState;
}

// When we set the state, the setter will return the amount of time that we should,
// remain in this state
int TimelineSlots::setCurrentState(const Status::State currentState){//, const int curTimeSlot) {
	int retVal = 0;
	this->currentState = currentState;
	//this->currentTimeSlot = curTimeSlot;

	switch(this->currentState)
	{
		case Status::State::IDLE:
		{
			retVal = 0;
			break;
		}
		case Status::State::DIFS:
		{
			retVal = this->slot.difsDuration;
			break;
		}
		case Status::State::SIFS:
		{
			retVal = this->slot.sifsDuration;
			break;
		}
		case Status::State::DATA:
		{
			retVal = this->slot.frameXmitt;
			break;
		}
		case Status::State::RTS:
		{
			retVal = this->slot.ackRtsCtsSize;
			break;
		}
		case Status::State::CTS:
		{
			retVal = this->slot.ackRtsCtsSize;
			break;
		}
		case Status::State::ACK:
		{
			retVal = this->slot.ackRtsCtsSize;
			break;
		}
		case Status::State::BOPERIOD:
		{
			retVal = this->slot.totalSim - this->mCurrentTimeSlot;
			break;
		}
		default:
		{
			retVal = -1;
			break;
		}
	}

	return(retVal);
}

const Slotted& TimelineSlots::getSlot() const {
	return slot;
}

void TimelineSlots::setSlot(const Slotted& slot) {
	this->slot = slot;
}

// This function will iterate in states, will; return true if
// we are passed the SimTime
Status::State TimelineSlots::iterateToState(const Status::State e, const int& setCurTime) {
	Status::State retVal = e;
	this->mCurrentTimeSlot = setCurTime;
	int timeReqForState = this->setCurrentState(e);

	if(this->mCurrentTimeSlot >= this->slot.totalSim )
	{
		timeReqForState = -1;
		return(Status::State::ENDOFSIM);
	}

	switch(this->currentState)
	{
		case Status::State::DIFS:
		{
			for(int j=0; j< timeReqForState;j++,increaseTimeSlot())
			{
				// Check If we can continue executing, SIM time boundary
				if(this->mCurrentTimeSlot >= this->slot.totalSim )
				{
					return(Status::State::ENDOFSIM);
				}
				// do Common stuff,
				doCommonStuff();
			}

			if( iterateToState(Status::State::BOPERIOD,this->mCurrentTimeSlot) == Status::State::ENDOFSIM)
			{
				return(Status::State::ENDOFSIM);
			}
			// example check if timeslot is equal to the time to transmit, if so,
			// select the BO count down
			break;
		}
		case Status::State::BOPERIOD:
		{
			for(int j=0; j< timeReqForState;j++,increaseTimeSlot())
			{
				// Check If we can continue executing, SIM time boundary
				if(this->mCurrentTimeSlot >= this->slot.totalSim )
				{
					return(Status::State::ENDOFSIM);
				}
				// do Common stuff,
				doCommonStuff();
				if(doBackOffPeriodStuff())
				{
					break; // Break for loop, someone wants to xmit
				}
			}
			// At this point we need to navigate to Data
			if( iterateToState(Status::State::DATA,this->mCurrentTimeSlot) == Status::State::ENDOFSIM)
			{
				return(Status::State::ENDOFSIM);
			}
			break;
		}
		case Status::State::DATA:
		{
			bool doneSetTxBegin = false;
			for(int j=0; j< timeReqForState;j++,increaseTimeSlot())
			{
				// Check If we can continue executing, SIM time boundary
				if(this->mCurrentTimeSlot >= this->slot.totalSim )
				{
					return(Status::State::ENDOFSIM);
				}

				if(!doneSetTxBegin)
				{
					for(VSI iT = this->vStations.begin();iT!=this->vStations.end();iT++)
					{
						Station &cur = *iT;
						cur.mTx.iBegin = this->mCurrentTimeSlot;
						cur.mTx.from = cur.getName();
						cur.mTx.to   = cur.getSendingTo();
						cur.mTx.TxCd   = cur.getCollisionDomain();
						cur.mTx.RxCd   = this->mMapStations[cur.getSendingTo()];
					}
					doneSetTxBegin = true;
				}
			}
			if( iterateToState(Status::State::SIFS,this->mCurrentTimeSlot) == Status::State::ENDOFSIM)
			{
				return(Status::State::ENDOFSIM);
			}
			break;
		}
		case Status::State::SIFS:
		{
			for(int j=0; j< timeReqForState;j++,increaseTimeSlot())
			{
				// Check If we can continue executing, SIM time boundary
				if(this->mCurrentTimeSlot >= this->slot.totalSim )
				{
					return(Status::State::ENDOFSIM);
				}

			}
			if( iterateToState(Status::State::ACK,this->mCurrentTimeSlot) == Status::State::ENDOFSIM)
			{
				return(Status::State::ENDOFSIM);
			}

			break;
		}
		case Status::State::ACK:
		{
//			cout << "ACK BEGIN " << this->mCurrentTimeSlot << endl;
			for(int j=0; j< timeReqForState;j++,increaseTimeSlot())
			{
				// Check If we can continue executing, SIM time boundary
				if(this->mCurrentTimeSlot >= this->slot.totalSim )
				{
					return(Status::State::ENDOFSIM);
					break;
				}

			}
//			cout << "ACK END " << this->mCurrentTimeSlot << endl;
			if(this->vXmits.size() == 1)
			{
				// success, only one station was trying to transmit
				this->vXmits[0]->resetBOSelectRange();
				this->vXmits[0]->mTx.iArrived = this->vXmits[0]->mFramesToXmit.front();
				this->vXmits[0]->mTx.iEnd   = this->mCurrentTimeSlot;

				if( this->vXmits[0]->mTx.iBegin > this->lastXmit.iArrived 	)
				{
					this->vXmits[0]->mFramesToXmit.pop_front();
					this->lastXmit = this->vXmits[0]->mTx;
					this->vXmits[0]->mGoodXmits.push_back(this->vXmits[0]->mTx);
					printf("HLVL: Tx by Station '%s' Arrived='%d' iBegin='%d' end='%d' \n",this->vXmits[0]->getName().c_str(),this->vXmits[0]->mTx.iArrived,this->vXmits[0]->mTx.iBegin,this->vXmits[0]->mTx.iEnd);
					this->vXmits.clear();
				}
				else
				{
					cout << "HLVL: Error, There was a collision " << endl;
				}


			}
			else
			{
				//TODO: Add cases where stations are not in the same collision domain
				for(std::vector<Station *>::iterator iT=this->vXmits.begin();iT!=this->vXmits.end();iT++)
				{
					Station *cur = *iT;
					cur->increaseBOSelectRange();
					cur->chooseBackOffTime();

				}
				this->vXmits.clear();
				cout << "HLVL: COLLISION!!! " << endl;
			}

			if( iterateToState(Status::State::DIFS,this->mCurrentTimeSlot) == Status::State::ENDOFSIM)
			{
				return(Status::State::ENDOFSIM);
			}
			break;
		}
		case Status::State::CTS:
		{
			// do Common stuff,
			doCommonStuff();
			//TODO
			break;
		}
		case Status::State::RTS:
		{
			// do Common stuff,
			doCommonStuff();
			// TODO
			break;
		}
		default:
		{
			cout << "what is this?" << endl;
			break;
		}
	}


	if(this->mCurrentTimeSlot >= this->slot.totalSim )
	{
		retVal = Status::State::ENDOFSIM;
	}

	return(retVal);
}

const std::vector<Station>& TimelineSlots::getStations() const {
	return vStations;
}

void TimelineSlots::setStations(const std::vector<Station>& stations) {
	if(!vStations.size())
	{
		vStations = stations;
		for(std::vector<Station>::iterator iT=vStations.begin() ; iT != vStations.end(); iT++)
		{
			printf("HLVL: Name of Station '%s'\n",(*iT).getName().c_str());

			 std::pair<std::map<std::string,COLLISION_DMN>::iterator,bool> ret;

			 ret = this->mMapStations.insert( std::make_pair((*iT).getName(),(*iT).getCollisionDomain()));
			 if(!ret.second){
				 cout << "ERROR: Key Already exists in mMapStations" << endl;
			 }
			/*
			 std::pair<std::map<std::string,int>::iterator,bool> ret;
			  ret = mymap.insert ( std::pair<char,int>('z',500) );
			  if (ret.second==false) {
				std::cout << "element 'z' already existed";
				std::cout << " with a value of " << ret.first->second << '\n';
			  }
			 */
		}
	}
}

void TimelineSlots::doCommonStuff(void) {
	for(std::vector<Station>::iterator iT = this->vStations.begin();iT!=this->vStations.end();iT++)
	{
		Station &cur = *iT;
		if(cur.mFramesToXmit.size() > 0   &&
		   cur.mFramesToXmit.front()	 <= this->mCurrentTimeSlot	)
		{
			cur.chooseBackOffTime();
		}
	}
}


bool TimelineSlots::doBackOffPeriodStuff (void) {
	bool retVal = false;
	bool boZeroSelect = false;

	// Before we start decrementing, we need to checm if someone selected zero
	for(VSI iT = this->vStations.begin();iT!=this->vStations.end();iT++)
	{
		Station &cur= *iT;
		if(cur.mFramesToXmit.size())
		{
			if(!cur.getBOCountDown())
			{
				this->vXmits.push_back(&cur);
				boZeroSelect = true;
				retVal = true;
			}
		}
	}

	if(!boZeroSelect)
	{
		for(VSI iT = this->vStations.begin();iT!=this->vStations.end();iT++)
		{
			Station &cur= *iT;
			if(cur.mFramesToXmit.size())
			{
				int curTimeSlot = this->mCurrentTimeSlot;
				bool boR = cur.decrementBOCounter(curTimeSlot,retVal);
				if(curTimeSlot > this->mCurrentTimeSlot)
				{
					increaseTimeSlot();
				}

				if(boR)
				{
					this->vXmits.push_back(&cur);
				}
				retVal = (retVal || boR );
			}
		}
	}


	return(retVal);
}

void TimelineSlots::addProbOfArrival(void) {
	for(VSI iT=this->vStations.begin();iT!=this->vStations.end();iT++)
	{
		Station &cur = *iT;
		if(cur.getTypeOfStation() == TYPEOFS::SENDER)
		{
			// TODO: The rate Packets/Second needs to be set on Statio initialization
			if(Random::get<bool>(0.006)) // true with 0.6% probability aka '300';
			{
				Station &curS = *iT;
				curS.mFramesToXmit.push_back(this->mCurrentTimeSlot);
				printf("Arrived packet on Station '%s' in TimeSlot '%d'\n",curS.getName().c_str(),this->mCurrentTimeSlot);	//std::cout << "Added to queue in slot i=" << i << endl;
			}
		}

	}
}

void TimelineSlots::setCurrentTimeSlot(int currentTimeSlot) {
	this->mCurrentTimeSlot = currentTimeSlot;
}

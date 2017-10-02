/*
 * StationClass.cpp
 *
 *  Created on: Sep 28, 2017
 *      Author: abc
 */
#include "Station.hpp"

#include <iostream>
#include "include/effolkronium/random.hpp" // https://github.com/effolkronium/random

using Random = effolkronium::random_static;
using namespace std;

// It takes 250 uS to xmit a frame  ~= 13 Slots
// Slot Duration 20 uS   ~= 50,000 Slots in a second
// SIFS Duration 10 uS ~= 1 Slot
// DIFS Duration 40 uS ~= 2 Slots
// Simulation time 10 S  ~= 500,000 Slots
// ACK, RTS, CTS size = 30 bytes ~= 5 uS ~= 1 Slot
// Transmission rate 6 Mbps

struct BO
{
	enum
	{
		RANGE3			=	3,
		RANGE7  		=	7,
		RANGE15     	=   15,
		RANGE31 		= 	31,
		RANGE63 		= 	63,
		RANGE127		=	127,
		RANGE255    	= 	255,
		RANGE511 		= 	511,
		RANGE1023		=	1023
	};
};


// Station ctor
Station::Station( const COLLISION_DMN cD, const TYPEOFS tyP, const std::string &nM, const std::string &nTo) :
mCollisionDomain(cD),
mTypeOfStation(tyP),
mBackOffCountDown(std::numeric_limits<int>::min()),
mBOSelectRng(BO::RANGE3),
mName(nM),
mSendingTo(nTo)
{


}

void Station::chooseBackOffTime(void)
{
	if(this->mBackOffCountDown == std::numeric_limits<int>::min())
	{
		srand (time(NULL));
		mBackOffCountDown =  Random::get(0,this->mBOSelectRng); // Select Random Value between (0,this->mBOSelectRng)
		cout << "Station " << mName.c_str() << " selected BoCntDown= " << mBackOffCountDown << endl;
	}
}

// This function increases the Back Off Select Range
void Station::increaseBOSelectRange(void)
{
	switch(this->mBOSelectRng)
	{
		case BO::RANGE3:
		{
			mBOSelectRng = BO::RANGE7;
			mBackOffCountDown = std::numeric_limits<int>::min();
			break;
		}
		case BO::RANGE7:
		{
			mBOSelectRng = BO::RANGE15;
			mBackOffCountDown = std::numeric_limits<int>::min();
			break;
		}

		case BO::RANGE15:
		{
			mBOSelectRng = BO::RANGE31;
			mBackOffCountDown = std::numeric_limits<int>::min();
			break;
		}
		case BO::RANGE31:
		{
			mBOSelectRng = BO::RANGE63;
			mBackOffCountDown = std::numeric_limits<int>::min();
			break;
		}
		case BO::RANGE63:
		{
			mBOSelectRng = BO::RANGE127;
			mBackOffCountDown = std::numeric_limits<int>::min();
			break;
		}
		case BO::RANGE127:
		{
			mBOSelectRng = BO::RANGE255;
			mBackOffCountDown = std::numeric_limits<int>::min();
			break;
		}
		case BO::RANGE255:
		{
			mBOSelectRng = BO::RANGE511;
			mBackOffCountDown = std::numeric_limits<int>::min();
			break;
		}
		default:
		{
			mBOSelectRng = BO::RANGE1023;
			mBackOffCountDown = std::numeric_limits<int>::min();
			break;
		}
	}
}

// This function resets the Back Off Select Range
void Station::resetBOSelectRange(void)
{
	this->mBOSelectRng = BO::RANGE3;
	this->mBackOffCountDown = std::numeric_limits<int>::min();
}

// This function returns the current Back Off Count Down
 const int &Station::getBOCountDown(void) const
{
	return(mBackOffCountDown);
}


// This function will decrement the BO Count Down
// If backOffCountDown == 0 the function will return true
// meaning that we will try to transmit a packet.
bool Station::decrementBOCounter(int &curTimeSlot, bool flagToInc)
{
	bool retVal = false;

	if(mBackOffCountDown != std::numeric_limits<int>::min() && mBackOffCountDown!=0)
	{
		mBackOffCountDown--;
		if(!mBackOffCountDown){
			if(!flagToInc){
				curTimeSlot++;
			}

			retVal = true;
		}
		else if(mBackOffCountDown < 0)
		{
			cout << "HLVL: Error, backOffCountDown should never be less than zero" << endl;
		}
		printf("HLVL: NEw boCountDown for Station '%s' is '%d' \n",this->mName.c_str(),mBackOffCountDown);
	}
	else
	{
		cout << "HLVL: Error, tried to decrement when backOffCountDown was = '" <<  mBackOffCountDown << "'" << endl;
	}

	return(retVal);
}

void Station::setCollisionDomain(COLLISION_DMN cD) {
	mCollisionDomain = cD;
}



TYPEOFS Station::getTypeOfStation() const {
	return mTypeOfStation;
}

void Station::setTypeOfStation(const TYPEOFS &typeOfStation) {
	mTypeOfStation = typeOfStation;
}

COLLISION_DMN Station::getCollisionDomain() const {
	return mCollisionDomain;
}

const std::string& Station::getName() const {
	return mName;
}

void Station::setName(const std::string& name) {
	this->mName = name;
}

const std::string& Station::getSendingTo() const {
	return mSendingTo;
}

void Station::setSendingTo(const std::string& sendingTo) {
	mSendingTo = sendingTo;
}

void Station::resetTxData(void) {
	this->mTx.iArrived 	= -1;
	this->mTx.iBegin   	= -1;
	this->mTx.iEnd		= -1;
}

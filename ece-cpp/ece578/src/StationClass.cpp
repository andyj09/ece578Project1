/*
 * StationClass.cpp
 *
 *  Created on: Sep 28, 2017
 *      Author: abc
 */
//#include "include/effolkronium/random.hpp" // https://github.com/effolkronium/random
#include <iostream>
#include "StationClass.hpp"
//#include "effolkronium/random.hpp"
#include "include/effolkronium/random.hpp"

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
		RANGE3		=	3,
		RANGE7  		=	7,
		RANGE15     =   15,
		RANGE31 		= 	31,
		RANGE63 		= 	63,
		RANGE127		=	127,
		RANGE255    	= 	255,
		RANGE511 	= 	511,
		RANGE1023	=	1023
	};
};


// Station ctor
StationClass::StationClass() :
mCollisionDomain(0),
mTypeOfStation(0),
backOffCountDown(0),
mBOSelectRng(BO::RANGE3)
{


}

void StationClass::chooseBackOffTime(void)
{

	srand (time(NULL));
	backOffCountDown =  Random::get(0,this->mBOSelectRng); // Select Random Value between (0,this->mBOSelectRng)

}

// This function increases the Back Off Select Range
void StationClass::increaseBOSelectRange(void)
{
	switch(this->mBOSelectRng)
	{
		case BO::RANGE3:
		{
			mBOSelectRng = BO::RANGE7;
			break;
		}
		case BO::RANGE7:
		{
			mBOSelectRng = BO::RANGE15;
			break;
		}

		case BO::RANGE15:
		{
			mBOSelectRng = BO::RANGE31;
			break;
		}
		case BO::RANGE31:
		{
			mBOSelectRng = BO::RANGE63;
			break;
		}
		case BO::RANGE63:
		{
			mBOSelectRng = BO::RANGE127;
			break;
		}
		case BO::RANGE127:
		{
			mBOSelectRng = BO::RANGE255;
			break;
		}
		case BO::RANGE255:
		{
			mBOSelectRng = BO::RANGE511;
			break;
		}
		default:
		{
			mBOSelectRng = BO::RANGE1023;
			break;
		}
	}
}

// This function resets the Back Off Select Range
void StationClass::resetBOSelectRange(void)
{
	this->mBOSelectRng = BO::RANGE31;
}

// This function returns the current Back Off Count Down
 const int &StationClass::getBOCountDown(void) const
{
	return(backOffCountDown);
}


// This function will decrement the BO Count Down
// If backOffCountDown == 0 the function will return true
// meaning that we will try to transmit a packet.
bool StationClass::decrementBOCounter(void)
{
	bool retVal = false;
	backOffCountDown--;
	if(!backOffCountDown){
		retVal = true;
	}
	else if(backOffCountDown < 0)
	{
		cout << "HLVL: Error, backOffCountDown should never be less than zero" << endl;
	}

	return(retVal);
}

void StationClass::setCollisionDomain(const int& cD) {
	mCollisionDomain = cD;
}

const int& StationClass::getCollisionDomain(void) const {
	return(mCollisionDomain);
}

int StationClass::getTypeOfStation() const {
	return mTypeOfStation;
}

void StationClass::setTypeOfStation(const int &typeOfStation) {
	mTypeOfStation = typeOfStation;
}

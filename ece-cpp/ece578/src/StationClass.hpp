/*
 * StationClass.hpp
 *
 *  Created on: Sep 28, 2017
 *      Author: abc
 */

#ifndef STATIONCLASS_HPP_
#define STATIONCLASS_HPP_

#include <deque>
class StationClass{
public:
	StationClass();
	void chooseBackOffTime(void);
	void increaseBOSelectRange(void);
	void resetBOSelectRange(void);
	const int &getBOCountDown(void) const;
	bool decrementBOCounter(void);
	void setCollisionDomain(const int & cD);
	const int &getCollisionDomain(void) const;
	int getTypeOfStation() const;
	void setTypeOfStation(const int &typeOfStation);

private:
	int mCollisionDomain; //
	int mTypeOfStation;   // Receiver ? Sender?
	int backOffCountDown;
	int mBOSelectRng;
	std::deque<int> framesToXmit;
};


#endif /* STATIONCLASS_HPP_ */

/*
 * StationClass.hpp
 *
 *  Created on: Sep 28, 2017
 *      Author: abc
 */

#ifndef STATIONCLASS_HPP_
#define STATIONCLASS_HPP_

#include <deque>
#include <string>
#include <vector>
#include <queue>

enum COLLISION_DMN{
	INVALID,
	ONE,
	TWO,
	THREE,
	NUMCOLLISIONDOMAINS
};
enum TYPEOFS{
	RECEIVER,
	SENDER
};

enum STATION_STATE {
	IDLE,
	DIFS_SENSING
};

struct TxData
{
	int iArrived;
	int iBegin;
	int iEnd;
	std::string from;
	std::string to;
	COLLISION_DMN RxCd; // Receiver Collision Domain
	COLLISION_DMN TxCd; // Transmitter Collision Domain
	TxData():iArrived(-1),iBegin(-1),iEnd(-1),RxCd(COLLISION_DMN::INVALID),TxCd(COLLISION_DMN::INVALID){}
};



class Station{
public:
	TxData mTx;
	std::vector<TxData> mGoodXmits;
	std::deque<int> mFramesToXmit;
	std::vector<double> poissonArrivlaTimes;
	std::queue<int> trueSlotArrival;

	Station(const COLLISION_DMN cD, const TYPEOFS tyP, const std::string &nM, const std::string &nTo);
	void chooseBackOffTime(void);
	void increaseBOSelectRange(void);
	void resetBOSelectRange(void);
	const int &getBOCountDown(void) const;
	bool decrementBOCounter(int &curTimeSlot, bool flagToInc);
	void setCollisionDomain(COLLISION_DMN cD);
	TYPEOFS getTypeOfStation() const;
	void setTypeOfStation(const TYPEOFS &typeOfStation);
	COLLISION_DMN getCollisionDomain() const;
	const std::string& getName() const;
	void setName(const std::string& name);
	void resetTxData(void);
	const std::string& getSendingTo() const;
	void setSendingTo(const std::string& sendingTo);
	int getNextFrameArriveSlot();
	void setState(STATION_STATE inState);
	STATION_STATE getState();
	int incrementStateCounter();
	int getStateCounter();
	void resetStateCounter();
private:
	COLLISION_DMN mCollisionDomain; //
	TYPEOFS mTypeOfStation;   // Receiver ? Sender?
	int mBackOffCountDown;
	int mBOSelectRng;
	std::string mName;
	std::string mSendingTo;
	STATION_STATE state;
	int stateCounter;
};


#endif /* STATIONCLASS_HPP_ */

/*
 * Train.cpp
 *
 *  Created on: Nov 6, 2012
 *      Author: rob
 */
#include "ABCList.hpp"
#include "LinkedList.hpp"
#include "Queue.hpp"
#include "Passenger.h"
#include "Train.h"


Train::~Train() {
	// TODO Auto-generated destructor stub
}

void Train::LoadPassengers(Queue<Passenger> *stationQ)
{
	int inTrain= passengers.getLength() ;

	int numberToLoad= maxCap - inTrain ;
	bool qEmpty= stationQ->isEmpty() ;
	for (int i= 0 ; i < numberToLoad && !qEmpty ; i++)
	{
		Passenger* curPassenger;
		stationQ->dequeue(&curPassenger);
		passengers.add(curPassenger);
		qEmpty= stationQ->isEmpty() ;
	}
}

void Train::GetXfers(Queue<Passenger> *xferQueue)
{
	int inTrain= passengers.getLength() ;

	for (int i= 0 ; i < inTrain; i++)
	{
		Passenger* curPassenger= passengers.retrieve(i + 1);
		if (curPassenger->transferRequired)
		{
			xferQueue->enqueue(curPassenger);
		}
	}

	for (int i= inTrain - 1 ; i >= 0; i--)
	{
		Passenger* curPassenger= passengers.retrieve(i + 1);
		if (curPassenger->transferRequired)
		{
			passengers.remove(i + 1) ;
		}	
	}
}

Passenger* Train::getArrived(enum Line id, int pos)
{
	int inTrain= passengers.getLength() ;

	Passenger* ret= NULL ;
	for (int i= 0 ; i < inTrain; i++)
	{
		Passenger* curPassenger= passengers.retrieve(i + 1);
		if (curPassenger->destLine == id && curPassenger ->destStationPos == pos)
		{
			ret= curPassenger ;
			passengers.remove(i + 1) ;
			break ;
		}
	}

	return ret ;
}

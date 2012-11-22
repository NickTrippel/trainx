/*
 * Station.cpp
 *
 *  Created on: Nov 6, 2012
 *      Author: rob
 */

#include <assert.h>
#include <fstream>
#include "ABCList.hpp"
#include "LinkedList.hpp"
#include "Queue.hpp"
#include "Station.h"
#include "Line.h"
#include "TrainSystem.h"
#include "Passenger.h"
#include "Train.h"

using namespace std;

	
Station::~Station() {
;	//TODO: implement when container is completed
}


//Line Station::getLine() const 
//{
//	return this->lineID;
//}

//Station* Station::getNextInbound ()
//{
//	return dispatcher->getStation(linePos-1);
//}

//Station* Station::getNextOutbound ()
//{
//	return dispatcher->getStation(linePos+1);
//}

// train queues for each station
void Station::AddTrain(enum Line line, enum eDirection dir, Train* train,  bool topOfQ)
{
	if (dir == INBOUND)
	{
		if (!topOfQ)
			inboundArrivals.enqueue(train);
		else
		{
			// top of queue, use for new train
		}
	}
	else
	{
		if (!topOfQ)
			outboundArrivals.enqueue(train);
		else
		{
			// top of queue, use for new train
		}
	
	}
}

#if 0
void Station::AddToOutbound(Train* train, bool topOfQ)
{
	if (!topOfQ)
		outboundArrivals.enqueue(train);
	else
	{
	
	}	
}
#endif

void Station::Initialize (TrainSystem *system, enum Line id, char type, int num)
{
	central= system;
	lineID= id;
	stationNo= num;
	assert (type == 'A' || type == 'B') ;
	stationType= type ;
}

void Station::Notify(CLine* route, enum eEvent event)
{
	if(event == UPDATE_CLOCK)
		AdvanceClock(route->GetLineID());
	else if (event == UPDATE_SIMULATION)
	{
		int newPassengers= GetNewPassengers();

		AddPassengersToEmbarkQ(route->GetLineID(), newPassengers);
		AdvanceTrains(route, OUTBOUND);  // originally first
		AdvanceTrains(route, INBOUND); 
		// AdvanceTrains(OUTBOUND);  // test order of execution
		//LoadTrains() ;
	}
}

void Station::AdvanceClock(enum Line id, int minutes)
{
	if (minutes == 1)
	{
		int cTrains = 0 ;      // count of Trains in station Queue
		Queue<Train> *qPtr;
	//Queue<Train> *oppositeQPtr;
		Train* cur;

		qPtr= &inboundArrivals ;
	
		cTrains= qPtr->getLength(); 
		
		for (int i = 0 ; i < cTrains ; i++)  // decrement ETA of each train in station Queue
		{
			cur= qPtr->retrieve(i+1);
			cur->decrementETA();
		}
		
		qPtr= &outboundArrivals;
		cTrains= qPtr->getLength(); 
		for (int i = 0 ; i < cTrains ; i++)  // decrement ETA of each train in station Queue
		{
			cur= qPtr->retrieve(i+1);
			cur->decrementETA();
		}
	}

}

void Station::AddPassengersToEmbarkQ(enum Line id, int newPassengers)
{
	for (int i= 0; i < newPassengers; i++)
	{
		enum Line destLine = INVALID ; // 
		int destPos = -1 ;
		GetRandomDestination (destLine, destPos);  // TO DO  // CHANGES w/ Time and properties file

		bool bInbound= true ;
		bool xfer= false ;
		central->FindDestination(lineID, linePos, destLine, destPos, bInbound, xfer);
		int sTime= central->GetTime() ;
		Passenger* p= new Passenger(id, linePos, destLine, destPos, xfer, sTime);


		
		//central->fout << "id: " << p->id << " O: " << (lineID == 0 ? "RED" : "BLUE") <<", " << linePos << " D: " 
		//	<< (destLine == 0 ? "RED" : "BLUE") << ", " << destPos << " ST: " << sTime << endl ;
		enum eDirection dir = INVALID_DIR;

		if (bInbound)
			dir = INBOUND ;
		else 
			dir = OUTBOUND ;
			
		Load(lineID, dir, p);
	}
}

void Station::AdvanceTrains(CLine* route, eDirection dir)  // PROBLEM - done only in outbound direction causing double decrement outbound
	// PROBLEM - need to decrement in OPPOSITE direction of Queue
{

	int cTrains = 0 ;      // count of Trains in station Queue
	Queue<Train> *qPtr;
	Queue<Train> *oppositeQPtr;
	Train* cur;
	int nextPos;

	if (dir == INBOUND)
	{
		qPtr= &inboundArrivals ;
		oppositeQPtr= &outboundArrivals ;
		nextPos= linePos - 1;
	}
	else
	{
		qPtr= &outboundArrivals;
		oppositeQPtr= &inboundArrivals;
		nextPos= linePos + 1;
	}

	cTrains= qPtr->getLength(); 
		
//	for (int i = 0 ; i < cTrains ; i++)  // decrement ETA of each train in station Queue
//	{
//		cur= qPtr->retrieve(i+1);
//		cur->decrementETA();
//	}

	if (cTrains > 0) //this
	{
		cur= qPtr->getFront();
		assert(cur!= 0);

		if ( (cur->getETA()) <= 0)
		{
			int timeToNext ;

			timeToNext= this->GetTimeToNext(route->GetLineID(), dir);
			UnloadTrain(route->GetLineID(), dir, cur);
			LoadTrain(route->GetLineID(), dir, cur);

			qPtr->dequeue() ;
			cur->setETA( timeToNext ) ;
			
			if (timeToNext == 0)  // if at the end of the line, add train to station Queues in opposite direction
			{
				// this
				// linePos
				//oppositeQPtr->addToFront(cur);
				enum eDirection oppDir ;
				if (dir == INBOUND)
					oppDir= OUTBOUND ;
				else
					oppDir= INBOUND ;

				LoadTrain(route->GetLineID(), oppDir, cur);
				if (dir == INBOUND)
				{
					nextPos= linePos + 1;
				}
				else
				{
					nextPos= linePos - 1;
				}
				LoadTrain(route->GetLineID(), oppDir, cur);

				Station*next=  route->getStation(nextPos);
				timeToNext= GetTimeToNext(route->GetLineID(), oppDir);
				cur->setETA( timeToNext) ;
				next->AddTrain(lineID, oppDir, cur);
				
			}
			else
			{
				// this code should never return a NULL
				// because the timeToNext == 0 case
				// should execute at the beginning and end of line
				Station*next=  route->getStation(nextPos);

				if (next == NULL)
				{// this
					int stophere= 1;
					assert(false);
				}
				
				next->AddTrain (lineID, dir, cur);
				
			}	
		}
	}
}


bool Station::arrived(CLine* route, enum eDirection dir, int &id, int& eta, int trainPos) // determine if train is at front of station train queue
{
	bool retVal= false;
	int inLine;
	id= 0;
	eta= -10;

	Queue<Train> *qPtr=NULL;

	if (dir == INBOUND)
		qPtr= &inboundArrivals ;
	else
		qPtr= &outboundArrivals ;

	int totalTrains= qPtr->getLength() ;

	if (totalTrains >= 1)
	{
		int stophere= true ;
	}

	if( (inLine= qPtr->getLength()) > 0)
	{
		eta= 9;
		Train* train= NULL ;

		if (trainPos == 1)
			train= qPtr->getFront();
		else if (trainPos <= totalTrains)
			train= qPtr->retrieve(trainPos);

		if (train != NULL)
		{
			int timeLeft;
			timeLeft= train->getETA ();
			eta= timeLeft;
			id=	train->getID() ;
			// our rule is we aren't supposed to set any train id to zero,
			// so if an actual train object has a 0 id, something's messed up
			assert(id != 0) ;

			if (timeLeft <= 0)
			{
				retVal= true;
			}
		}
	}

	return retVal ;
}
#if 0
bool Station::outboundArrived(CLine* route, int &id, int& eta, int trainPos)  // determine if train is at front of station train queue
{
	bool retVal= false;
	int inLine;
	id= 0;
	eta= -10;
	int totalTrains= outboundArrivals.getLength() ;

	if( (inLine= outboundArrivals.getLength()) > 0)
	{
		eta= 9;
		Train* train= NULL;

		if (trainPos == 1)
			train = outboundArrivals.getFront() ;
		else if (trainPos <= totalTrains)
			train= outboundArrivals.retrieve(trainPos) ;

		if(train != NULL)
		{
			int timeLeft;
			timeLeft= train->getETA ();
			eta= timeLeft;
			id=	train->getID() ;
			if (timeLeft <= 0)
			{
				retVal= true;
			}
		}
	}

	return retVal ;
}
#endif

int Station::GetNewPassengers()  // TO DO
{
	return 1 ;
}

void Station::GetRandomDestination (enum Line &line, int &num)  // TO DO
{
//#define NO_TRANSFERS
#ifdef NO_TRANSFERS
	line= lineID ;
#else
	enum Line stationLines[] = {RED, RED, BLUE, RED, BLUE};
	static int lineIndex ;

	int lineMax= sizeof (stationLines)/ sizeof (enum Line);
	int curLine= (++lineIndex)%lineMax ;
	line= stationLines[curLine] ;
#endif
	
	
	int redMax= 7; 
	int blueMax= 4 ;
	static int stationNumCounter;

	if (line == RED)
		num= ((++stationNumCounter)%redMax) + 1;
	else
		num= ((++stationNumCounter)%blueMax) + 1;
}


void Station::LoadTrain(enum Line id, enum eDirection dir, Train* t)
{
	Queue<Passenger> *qPtr= NULL ;

	if (linePos == 1)
	{
		if ((t->getID()) == 6)
		{
			int stophere= 1;
		}
	}
	if (dir == INBOUND)
		qPtr= &inboundPassengers;
	else
		qPtr= &outboundPassengers;

	t->LoadPassengers(qPtr);
}


void Station::UnloadTrain(enum Line id, enum eDirection dir, Train* t)
{
	Passenger* p= NULL ;

	do
	{
		p= t->getArrived(lineID, linePos);
		if (p != NULL)
		{
			int aTime= central->GetTime () ;

			central->fout << "Arrived id:" << p->id 
				<<" O: " << (p->originLine == 0 ? "RED" : "BLUE") <<", " << p->originStationPos
				<< " D: " << (p->destLine == 0 ? "RED" : "BLUE") 
				<< ", " << p->destStationPos << " T: " << p->startTime << " to " << aTime << endl ;
			delete p ;
			int test= 1;			
			// figure if time out
			// if yes log 
		}

	} while (p != NULL) ;
}


void Station::AddNewTrain(enum Line id, eDirection dir)
{
	static int trainCounter;
	Train* t= new Train();
	t->Initialize(++trainCounter);

	if (dir == OUTBOUND)
	{
		t->setETA(0);
		outboundArrivals.addToFront(t);
	}
	else
	{
		t->setETA(0);
		inboundArrivals.addToFront(t);
	}
}

int Station::GetTimeToNext(enum Line id, enum eDirection dir)
{
	int ret= -1 ;

	if (dir == INBOUND)
		ret= timeToNextInbound;
	else
		ret= timeToNextOutbound;

	return ret ;
}

void Station::SetTimeToNext(enum Line id, enum eDirection dir, int newTime)
{
	assert (dir == INBOUND || dir == OUTBOUND) ;

	if (dir == INBOUND)
		timeToNextInbound= newTime ;
	else
		timeToNextOutbound= newTime;

}

void MultiLineStation::AddTrain(enum Line id, enum eDirection dir, Train* train,  bool topOfQ)
{
	StationQueues* route = NULL ;

	if (id == BLUE)
		route = &blueRoute ;
	else
		route = &redRoute ;

	if (dir == INBOUND)
	{
		if (!topOfQ)
			route->inboundArrivals.enqueue(train);
		else
		{
			// top of queue, use for new train
		}
	}
	else
	{
		if (!topOfQ)
			route->outboundArrivals.enqueue(train);
		else
		{
			// top of queue, use for new train
		}
	}
}





void MultiLineStation::AdvanceClock(enum Line id, int minutes)
{
		StationQueues* queues= NULL ;
			
		if (id == BLUE)
			queues= &blueRoute;
		else
			queues= &redRoute;

	if (minutes == 1)
	{
		int cTrains = 0 ;      // count of Trains in station Queue
		Queue<Train> *qPtr;
	//Queue<Train> *oppositeQPtr;
		Train* cur;

		qPtr= &queues->inboundArrivals ;
	
		cTrains= qPtr->getLength(); 
		
		for (int i = 0 ; i < cTrains ; i++)  // decrement ETA of each train in station Queue
		{
			cur= qPtr->retrieve(i+1);
			cur->decrementETA();
		}
		
		qPtr= &queues->outboundArrivals;
		cTrains= qPtr->getLength(); 
		for (int i = 0 ; i < cTrains ; i++)  // decrement ETA of each train in station Queue
		{
			cur= qPtr->retrieve(i+1);
			cur->decrementETA();
		}
	}

}

void MultiLineStation::AddPassengersToEmbarkQ(enum Line id, int newPassengers)
{
	StationQueues* queues= NULL ;
			

	for (int i= 0; i < newPassengers; i++)
	{
		enum Line destLine = INVALID ; // 
		int destPos = -1 ;
		GetRandomDestination (destLine, destPos);  // TO DO  // CHANGES w/ Time and properties file

		bool bInbound= true ;
		bool xfer= false ;

		if (destLine == BLUE)
			queues= &blueRoute;
		else
			queues= &redRoute;

		central->FindDestination(destLine, queues->linePos, destLine, destPos, bInbound, xfer);
		
		// never need to transfer
		assert(xfer == false) ;

		enum Line originLine= destLine ; // we can choose the orginLine to be the destLine because
		// they are in the same station
		
		Passenger* p= new Passenger(originLine, queues->linePos, destLine, destPos, xfer, central->GetTime());
		
		enum eDirection dir = INVALID_DIR;

		if (bInbound)
			dir = INBOUND ;
		else 
			dir = OUTBOUND ;
			
		Load(destLine, dir, p);
	}
}


void MultiLineStation::Initialize (TrainSystem *system, enum Line id1, enum Line id2, char type, int num)
{
	// this
	central= system;
	assert (id1 == RED) ;
	assert (id2 == BLUE) ;
	redRoute.lineID= id1;
	blueRoute.lineID= id2;
	stationNo= num;
	assert (type == 'A' || type == 'B') ;
	stationType= type ;
}

void MultiLineStation::setLinePos(enum Line id, int pos)
{
	if (id == RED)
		redRoute.linePos= pos;  // called by CLine object so station knows position
	else if (id == BLUE)
		blueRoute.linePos= pos;  
	else
	{
		assert(false) ;
	}
}

bool MultiLineStation::arrived(CLine* route, enum eDirection dir, int &trainID, int& eta, int trainPos) // determine if train is at front of station train queue
{
	StationQueues* queues= NULL ;

	if (route->GetLineID() == BLUE)
		queues= &blueRoute;
	else
		queues= &redRoute;

	bool retVal= false;
	int inLine;
	trainID= 0;
	eta= -10;

	Queue<Train> *qPtr= NULL ;

	if (dir == INBOUND)
		qPtr= &queues->inboundArrivals ;
	else
		qPtr= &queues->outboundArrivals ;

	int totalTrains= qPtr->getLength() ;

	if( (inLine= qPtr->getLength()) > 0)
	{
		eta= 9;
		Train* train= NULL ;

		if (trainPos == 1)
			train= qPtr->getFront();
		else if (trainPos <= totalTrains)
			train= qPtr->retrieve(trainPos);

		if (train != NULL)
		{
			int timeLeft;
			timeLeft= train->getETA ();
			eta= timeLeft;
			trainID=	train->getID() ;
			// our rule is we aren't supposed to set any train id to zero,
			// so if an actual train object has a 0 id, something's messed up
			assert(trainID != 0) ;

			if (timeLeft <= 0)
			{
				retVal= true;
			}
		}
	}

	return retVal ;
}

int MultiLineStation::GetTimeToNext(enum Line id, enum eDirection dir)
{
	int ret= -1 ;

	StationQueues* queues= NULL ;
			
	if (id == BLUE)
		queues= &blueRoute;
	else
		queues= &redRoute;

	if (dir == INBOUND)
		ret= queues->timeToNextInbound;
	else
		ret= queues->timeToNextOutbound;

	return ret ;
}

void MultiLineStation::SetTimeToNext(enum Line id, enum eDirection dir, int newTime)
{
	assert (dir == INBOUND || dir == OUTBOUND) ;

		StationQueues* queues= NULL ;
			
	if (id == BLUE)
		queues= &blueRoute;
	else
		queues= &redRoute;

	if (dir == INBOUND)
		queues->timeToNextInbound= newTime ;
	else
		queues->timeToNextOutbound= newTime;

}


void MultiLineStation::GetRandomDestination (enum Line &line, int &num)  // TO DO
{
	Station::GetRandomDestination (line, num) ;
}

MultiLineStation::~MultiLineStation() {
;	//TODO: implement when container is completed
}


void MultiLineStation::AdvanceTrains(CLine* route, eDirection dir)  // PROBLEM - done only in outbound direction causing double decrement outbound
	// PROBLEM - need to decrement in OPPOSITE direction of Queue
{

	StationQueues* queues= NULL ;

	enum Line curLineID= route->GetLineID() ;

	// don't want to inherit linePos since there can be more than one in MultiLineStation
	if (curLineID == BLUE)
		queues= &blueRoute;
	else
		queues= &redRoute;

	

	int cTrains = 0 ;      // count of Trains in station Queue
	Queue<Train> *qPtr;
	Queue<Train> *oppositeQPtr;
	Train* cur;
	int nextPos;
	
	if (dir == INBOUND)
	{
		qPtr= &queues->inboundArrivals ;
		oppositeQPtr= &queues->outboundArrivals ;
		nextPos= queues->linePos - 1;
	}
	else
	{
		qPtr= &queues->outboundArrivals;
		oppositeQPtr= &queues->inboundArrivals;
		nextPos= queues->linePos + 1;
	}

	cTrains= qPtr->getLength(); 
		
//	for (int i = 0 ; i < cTrains ; i++)  // decrement ETA of each train in station Queue
//	{
//		cur= qPtr->retrieve(i+1);
//		cur->decrementETA();
//	}

	if (cTrains > 0)
	{
		cur= qPtr->getFront();
		assert(cur!= 0);

		if ( (cur->getETA()) <= 0)
		{
			int timeToNext ;

			timeToNext= this->GetTimeToNext(route->GetLineID(), dir);
			UnloadTrain(route->GetLineID(), dir, cur);
			LoadTrain(route->GetLineID(), dir, cur);

			qPtr->dequeue() ;
			cur->setETA( timeToNext ) ;
			
			if (timeToNext == 0)  // if at the end of the line, add train to station Queues in opposite direction
			{
				// this
				// linePos
				//oppositeQPtr->addToFront(cur);
				enum eDirection oppDir ;
				if (dir == INBOUND)
					oppDir= OUTBOUND ;
				else
					oppDir= INBOUND ;

				LoadTrain(route->GetLineID(), oppDir, cur);
				if (dir == INBOUND)
				{
					nextPos= queues->linePos + 1;
				}
				else
				{
					nextPos= queues->linePos - 1;
				}
				LoadTrain(route->GetLineID(), oppDir, cur);

				Station*next=  route->getStation(nextPos);
				timeToNext= GetTimeToNext(route->GetLineID(), oppDir);
				cur->setETA( timeToNext) ;
				next->AddTrain(curLineID, oppDir, cur);
				
			}
			else
			{
				// this code should never return a NULL
				// because the timeToNext == 0 case
				// should execute at the beginning and end of line
				Station*next=  route->getStation(nextPos);

				if (next == NULL)
				{// this
					int stophere= 1;
					assert(false);
				}
				
				next->AddTrain (curLineID, dir, cur);
				
			}	
		}
	}
}

//void MultiLineStation::LoadTrains() 
//{
//	// load last 
//}

int MultiLineStation::GetNewPassengers()  // TO DO
{
	return Station::GetNewPassengers();
}

void MultiLineStation::AddNewTrain(enum Line id, eDirection dir)
{
	static int trainCounter;
	Train* t= new Train();
	t->Initialize(++trainCounter);

	StationQueues* queues= NULL ;
		
	if (id == BLUE)
		queues= &blueRoute;
	else
		queues= &redRoute;

	if (dir == OUTBOUND)
	{
		t->setETA(0);
		queues->outboundArrivals.addToFront(t);
	}
	else
	{
		t->setETA(0);
		queues->inboundArrivals.addToFront(t);
	}
}

void Station::Load(enum Line ID, enum eDirection dir, Passenger* p)
{
	Queue<Passenger> *qPtr ;
	
	if (dir == OUTBOUND)
		qPtr= &outboundPassengers;
	else
		qPtr= &inboundPassengers;
		
	qPtr->enqueue(p);
};

void MultiLineStation::Load(enum Line id, enum eDirection dir, Passenger* p)
{
	Queue<Passenger> *qPtr ;

	StationQueues* queues= NULL ;
		
	if (id == BLUE)
		queues= &blueRoute;
	else
		queues= &redRoute;

	if (dir == OUTBOUND)
		qPtr= &queues->outboundPassengers;
	else
		qPtr= &queues->inboundPassengers;
		
	qPtr->enqueue(p);
};

void MultiLineStation::LoadTrain(enum Line id, enum eDirection dir, Train* t)
{
	Queue<Passenger> *qPtr ;

	StationQueues* queues= NULL ;
		
	if (id == BLUE)
		queues= &blueRoute;
	else
		queues= &redRoute;

	if (dir == INBOUND)
		qPtr= &queues->inboundPassengers;
	else
		qPtr= &queues->outboundPassengers;

	t->LoadPassengers(qPtr);
}

void MultiLineStation::UnloadTrain(enum Line id, enum eDirection dir, Train* t)
{
	Queue<Passenger> *qPtr ;
	Queue<Passenger> tempQ;

	StationQueues* queues= NULL ;
		
	// switch to other line for transfers
	if (id == BLUE)
		queues= &redRoute;
	else
		queues= &blueRoute;
	

	Passenger* curPassenger= NULL ;
	t->GetXfers(&tempQ);

	while (!tempQ.isEmpty())
	{
		tempQ.dequeue(&curPassenger);

		if ((curPassenger->destLine == BLUE && curPassenger->destStationPos == 3)
			|| (curPassenger->destLine == RED && curPassenger->destStationPos == 5))
		{
			ProcessOutGoing(curPassenger) ;
		}
		else
		{
			assert (curPassenger->transferRequired == true) ;
		assert (curPassenger->destLine != id);
		// again we use the destination id and pos instead the 
		// line we actually arrived, because don't need that info
		bool inBound ;
		bool xferStub ;

		central->FindDestination(queues->lineID, queues->linePos, 
			curPassenger->destLine, curPassenger->destStationPos, inBound, xferStub) ;
		
		assert(!xferStub) ;
	
		if (inBound)
			qPtr= &queues->inboundPassengers ;
		else
			qPtr= &queues->outboundPassengers ;
		
		// set time for transfer point waiting here
		qPtr->enqueue(curPassenger) ;
		}
		
	}

	// point queues back to arriving side
	if (id == BLUE)
		queues= &blueRoute;
	else
		queues= &redRoute;
	do
	{
		curPassenger= t->getArrived(queues->lineID, queues->linePos);
		if (curPassenger != NULL)
		{
			ProcessOutGoing(curPassenger) ;
		}

	} while (curPassenger != NULL) ;
}

void MultiLineStation::ProcessOutGoing (Passenger* p)
{
	int aTime= central->GetTime () ;
	central->fout <<"Arrived id:" << p->id <<" O: " << (p->originLine == 0 ? "RED" : "BLUE") <<", " << p->originStationPos << " D: " 
		<< (p->destLine == 0 ? "RED" : "BLUE") << ", " << p->destStationPos << " T: " << p->startTime << " to " << aTime << endl ;
	delete p ;
}
#include <iostream>
#include <fstream>
#include <assert.h>
#include "ABCList.hpp"
#include "LinkedList.hpp"
#include "Queue.hpp"
#include "Station.h"
#include "Line.h"
#include "TrainSystem.h"


void CLine::Initialize (TrainSystem* tsys)
{
	outboundStations=  new LinkedList<Station>;
	central= tsys;
}

void CLine::NotifyStations()  // loops through Cline route 
{
	if (displayOn)
		DisplayTrainsSnapShots(this, 3); //3 minutes at a time, totally arbitrary

	int total= outboundStations->getLength() ;
	for (int i= 0; i < total ; i++)
	{
		Station* s= outboundStations->retrieve(i+1);
		if (s != NULL)
			s->Notify(this, UPDATE_CLOCK) ;
	}

	for (int i= 0; i < total ; i++)
	{
		Station* s= outboundStations->retrieve(i+1);
		if (s != NULL)
			s->Notify(this, UPDATE_SIMULATION) ;
	}
}

void CLine::DisplayTrainsInQueue(CLine* route, int stationPos, eDirection dir, int nTrains)
{
		Queue<Train> *qPtr= NULL ;
		Station* s= outboundStations->retrieve(stationPos);
		cout << "|";
		for (int j= 0; j < nTrains; j++)
		{
				int trainID= 0;
				int eta= 0;
				
 				if (s != NULL)
				{
					char chID ;
					bool arrived ;
					arrived= s->arrived(route, dir, trainID, eta, j+1);
					

					if(trainID != 0)
					{
						chID= '0' + (trainID);
						cout << chID ;
						chID= '0' + (eta);
						cout << chID ;
					}
					else
					{
						chID= 'X';
						cout << chID ;
						chID= 'X';
						cout << chID ;
					}
				}
				
		}
		cout << "|";
}

void CLine::DisplayTrainsSnapShots(CLine* route, int howMuchTime)
{
	static int callCounter;
	callCounter++ ;
	if (howMuchTime < 0 || howMuchTime > 10)
		howMuchTime = 1;
	
	DisplayTrains (route);
	
	if (howMuchTime == 1 || callCounter%howMuchTime == 0)
	{
	std::cin.clear() ;
	std::cout << "Press ENTER to continue... " << flush;
	std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
	std::cin.get() ;
	}
}

void CLine::DisplayTrains(CLine* route)
{
	string sInbound=  "INBOUND:  ";
	string sOutbound= "OUTBOUND: ";

	int total= outboundStations->getLength();

	cout << "Time is " << central->GetTime() << endl;

	cout << sInbound ;
	bool arrived= false ;
	for (int i= 0; i < total ; i++)
	{
		DisplayTrainsInQueue(route, i+1, INBOUND, 3);
	}
	cout << endl;

	cout << sOutbound ;
	for (int i= 0 ; i < total ; i++)// is this right?
	{
			DisplayTrainsInQueue(route, i+1, OUTBOUND, 3);
	}

	cout << endl;

}

void CLine::AddStation(Station *newStation)  // add stations to lines  
{												
	// neeeds atttention, make sure position logic is right
	// top of route has to have timeToNextInbound as 0
	// bottom of route has to have timeToNexOutbound as 0
	// outbound is the positive direction (pos increases) from top of list

	int lastPos= outboundStations->getLength();
	Station* preceeding ;
	if (lastPos > 0)
		preceeding= outboundStations->retrieve(lastPos);
	
	newStation->SetTimeToNext(lineID, INBOUND, 0) ;
	newStation->SetTimeToNext (lineID, OUTBOUND, 0) ; //if last station added, this won't get reset by sucessive stations, remains 0 
	
	
	if (lastPos == 0) //empty list
	{
	}
	else 
	{
		char newStationType= newStation->GetStationType ();
		char preceedingStationType= preceeding->GetStationType () ;

		if (newStationType != preceedingStationType)  // unmatched station types (A vs. B) have 8 min transit time
		{
			newStation->SetTimeToNext(lineID, INBOUND, 8) ;
			preceeding->SetTimeToNext(lineID, OUTBOUND, 8) ;
		}
		else
		{
			// all trips between stations of the same type are 2 min
			newStation->SetTimeToNext(lineID, INBOUND, 2) ;
			preceeding->SetTimeToNext(lineID, OUTBOUND, 2) ;
		}
	}

		cout << "lastPos: " << lastPos << endl ;
		cout << "timeToNextInbound: " << newStation->GetTimeToNext(lineID, INBOUND) << endl  ;
		if (lastPos != 0)//empty list
			cout << "timeToNextOutbound: " << preceeding->GetTimeToNext(lineID, OUTBOUND) << endl ;

	//newStation->attachToLine (this);
	newStation->setLinePos(lineID, lastPos+1);

	// presuppose only one transfer (i.e one MultiLineStation object) per line
	if (newStation->isTransfer())
	{
		xferPos= lastPos + 1;
	}

	outboundStations->insert(lastPos + 1, newStation);
}

Station* CLine::getStation(int pos)
{
	Station* ret= NULL ;
	int size= outboundStations->getLength();

	if (pos > 0 && pos <= size)
	{
		ret= outboundStations->retrieve(pos);
	}

	return ret;
}


// pos = position on the route (RED = 1 thru 7 || BLUE = 1 thru 4) 
// dir = direction on the route ( INBOUND || OUTBOUND) 
void CLine::PlaceTrain(int pos, eDirection dir) 
{
	int total= outboundStations->getLength();
	assert (pos > 0 && pos <= total);
	Station *s= outboundStations->retrieve(pos);
	s->AddNewTrain(lineID, dir);
}
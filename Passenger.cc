/**
 * Title: Passenger.cc
 * Date: November 7, 2012
 * Author(s): Robert O'Connor/Nick Trippel
 * Description: represents a train car as a part of the Train.
 */
#include "Passenger.h"

static long pCounter ;
Passenger::Passenger(enum Line oLine, int oStationPos, enum Line dLine, int dStationPos, bool xfer, int nTime) :
		  id (++pCounter),
			  startTime(nTime),
		waitTime(0),
		  travelTime(0),
		  originLine(oLine),
		  originStationPos(oStationPos),
		  destLine(dLine),
		  destStationPos(dStationPos),
		  transferRequired(xfer)
		{};

Passenger::~Passenger() {

}

/**
 * Title: Passenger.h
 * Date: November 7, 2012
 * Author(s): Robert O'Connor/Nick Trippel
 * Description: represents a Passenger (either in the Station or in a Car on the Train
 */

#ifndef PASSENGER_H_
#define PASSENGER_H_

class Passenger {
	public:
		Passenger(enum Line oLine, int oStationPos, enum Line dLine, int dStationPos, bool xfer, int nTime) ;
		
		virtual ~Passenger();
		//private:
		long id ;
		int startTime ;
		int waitTime;
		int travelTime;
		enum Line originLine ;
		int  originStationPos ;
		enum Line destLine;
		int  destStationPos;
		bool transferRequired;


};

#endif /* PASSENGER_H_ */

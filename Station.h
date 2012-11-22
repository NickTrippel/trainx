/**
 * Title: Station.h
 * Name: Robert O'Connor and Nick Trippel
 * Date: November 6, 2012
 * Description: Represents a train station within the train system
 *
 */

#ifndef STATION_H_
#define STATION_H_

//#include "Line.h" // the enumerated type for the line

class TrainSystem;
class Train ;
class Passenger;
class CLine;
//template<> class Queue<Train>{};   // new syntax
#include "Queue.hpp"

#include <string> 


using std::string ;

enum eDirection ;

class Station {
	public:
		// There is no default constructor -- this is a design decision.

		/**
		 * The name of the station and the line may not change.
		 * The only thing that is not constant is the trains queue
		 * @param the name of the station
		 * @param the line (of type enumerated type Line)
		 */
		Station()
		{
		
		}
		
		void Notify(CLine* route, enum eEvent event);
		/*
		 * destructor...
		 */
		virtual ~Station();

		void Initialize (TrainSystem *system, enum Line id, char type, int num);
					
		/**
		 * Gets the station name
		 * @return the station name
		 */
		//std::string getName() const;

		/**
		 * gets the line name (RED,BLUE or TRANSFER).
		 */
		//Line getLine() const;

//		void attachToLine(CLine *myLine){
//			dispatcher= myLine ;
//		};
		virtual void setLinePos(enum Line id, int pos)
		{
			linePos= pos;  // called by CLine object so station knows position
		};
		virtual bool arrived(CLine*, enum eDirection dir, int &trainId, int& eta, int trainPos= 1);
		//virtual bool outboundArrived(CLine*, int &id, int& eta, int trainPos= 1);

		virtual void UnloadTrain(enum Line, enum eDirection,Train*);   // TO DO
		virtual void LoadTrain(enum Line, enum eDirection,Train*);     // TO DO
		virtual void AdvanceClock(enum Line id, int minutes= 1);

		// train queues for each station  // TO DO
		virtual void AddTrain(enum Line, enum eDirection, Train* ,  bool topOfQ= false);
		//virtual void AddToOutbound(Train* , bool topOfQ= false);
		virtual int GetTimeToNext(enum Line, enum eDirection) ;		
		virtual void SetTimeToNext(enum Line, enum eDirection, int) ;		
		// these are identifiers that come from the prof, mostly not used
		
		virtual void AddNewTrain(enum Line lineID, eDirection dir);
		virtual bool isTransfer () { return false ;} ;
		char GetStationType () {return stationType;};
		
		//virtual enum Line GetLine() ;
		//virtual int GetLinePos() ;
	protected:
		char stationType ; // 'A' or 'B'
		int	 stationNo ;   // identifier, not position!
		TrainSystem *central;  // where info is logged about stations
		virtual void GetRandomDestination (enum Line &line, int &num);
		virtual void AddPassengersToEmbarkQ(enum Line id, int newPassengers);
		virtual void AdvanceTrains(CLine* route, eDirection dir);
		//virtual void LoadTrains(enum Line id) ;
		virtual int GetNewPassengers();
		//virtual Station* getNextInbound ();
		//virtual Station* getNextOutbound ();
		virtual void Load(enum Line ID, enum eDirection dir, Passenger* p);
		
	private:
		enum Line lineID;
		int linePos ;  // Position in Linked List

		int timeToNextOutbound;
		int timeToNextInbound;
		

		// these are identifiers that come from the prof, mostly not used


		

		//string name;
		
		
		
		/**
		 * The name of the station
		 */

		Queue<Train> inboundArrivals ;
		Queue<Train> outboundArrivals ;

		Queue<Passenger> inboundPassengers ; // one or more
		Queue<Passenger> outboundPassengers ;

		
		//void SendOutbound(Passenger* p)
		//{
		//	inboundPassengers.enqueue(p);
		//};
		
		/*** The stations Line  	*/
		
			

		/**
		 * The trains that are at this station...
		 */
		//TODO: implement List

		/**
		 * Passengers waiting at the station
		 *
		 */
		//TODO: implement Queue
};

class StationQueues
{
public:
	Queue<Train> inboundArrivals ;
	Queue<Train> outboundArrivals ;
	
	Queue<Passenger> inboundPassengers ; // one or more
	Queue<Passenger> outboundPassengers ;
	enum Line lineID;
	int linePos ;  // Position in Linked List
	int timeToNextOutbound;
	int timeToNextInbound;
};

class MultiLineStation : public Station
{
	public:
		// There is no default constructor -- this is a design decision.

		/**
		 * The name of the station and the line may not change.
		 * The only thing that is not constant is the trains queue
		 * @param the name of the station
		 * @param the line (of type enumerated type Line)
		 */
		MultiLineStation():Station()
		{
		
		}
		
		void Notify(CLine*, enum eEvent event);
		/*
		 * destructor...
		 */
		virtual ~MultiLineStation();

		virtual void Initialize (TrainSystem *system, enum Line id1, enum Line id2, char type, int num);
			
		/**
		 * Gets the station name
		 * @return the station name
		 */
		//std::string getName() const;

		/**
		 * gets the line name (RED,BLUE or TRANSFER).
		 */
		//Line getLine() const;

//		void attachToLine(CLine *myLine){
//			dispatcher= myLine ;
//		};
		virtual void setLinePos(enum Line id, int pos);
		virtual bool arrived(CLine*, enum eDirection dir, int &trainId, int& eta, int trainPos= 1);
		//virtual bool inboundArrived(CLine*, int &id, int& eta, int trainPos= 1);
		//virtual bool outboundArrived(CLine*, int &id, int& eta, int trainPos= 1);
		
		virtual void UnloadTrain(enum Line, enum eDirection,Train*);   // TO DO
		virtual void LoadTrain(enum Line, enum eDirection,Train*);     // TO DO
		
		virtual void AdvanceClock(enum Line id, int minutes= 1);

		// train queues for each station  // TO DO
		virtual void AddTrain(enum Line, enum eDirection, Train* ,  bool topOfQ= false);
		virtual void AddNewTrain(enum Line lineID, eDirection dir);
		virtual int GetTimeToNext(enum Line, enum eDirection) ;		
		virtual void SetTimeToNext(enum Line, enum eDirection, int) ;		
		virtual bool isTransfer () { return true ;} ;
		virtual void Load(enum Line id, enum eDirection dir, Passenger* p);

		// these are identifiers that come from the prof, mostly not used
		//char stationType ; // 'A' or 'B'
		//int	 stationNo ;   // identifier, not position!
		//virtual void AddTrain(eDirection dir);
		//virtual enum Line GetLine() ;
		//virtual int GetLinePos() ;
	protected:
		virtual void GetRandomDestination (enum Line &line, int &num);
		//virtual void LoadTrains(enum Line id) ;
	private:

		// these are identifiers that come from the prof, mostly not used
		int GetNewPassengers();
		void ProcessOutGoing(Passenger*) ;

		void AddPassengersToEmbarkQ(enum Line id, int newPassengers);
		void AdvanceTrains(CLine* route, eDirection dir);
		
		//string name;
		
		Station* getNextInbound ();
		Station* getNextOutbound ();
		
		/**
		 * The name of the station
		 */
		StationQueues redRoute;
		StationQueues blueRoute;
				
		//void SendOutbound(Passenger* p)
		//{
		//	inboundPassengers.enqueue(p);
		//};
		
		/*** The stations Line  	*/
		
		//CLine *dispatcher;
		//TrainSystem *central;  // where info is logged about stations

		/**
		 * The trains that are at this station...
		 */
		//TODO: implement List

		/**
		 * Passengers waiting at the station
		 *
		 */
		//TODO: implement Queue
};

#endif /* STATION_H_ */

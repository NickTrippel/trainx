/**
 * Title: TrainSystem.h
 * Date: November 7, 2012
 * Author(s): Robert O'Connor/Nick Trippel
 * Description: represents the system of trains
 */



#ifndef TRAINSYSTEM_H_
#define TRAINSYSTEM_H_


class TrainSystem {
	public:
		TrainSystem():  timeCounter(0), endHour(22), endMinute(0)
		{
			
		}

		void FindDestination(enum Line lineOfOrigin, int stationPosOfOrigin, 
				enum Line lineOfDestination, int stationPosOfDestination,bool &bInbound, bool &xfer );
		void Start(int numberOfTrains, int hour= 6, int minute= 0); // may need different numberOfTrains for different lines
		void DisplayStats() ;  // TO DO
		int GetTime() {return timeCounter;};  
		ofstream fout ;
		//virtual ~TrainSystem();
		~TrainSystem() { fout.close();};
		
	private:
		void Initialize() ;
		// PlaceTrains might be CLine method rather than TrainSystem
		//void PlaceTrains() ;  // TO DO  // SHOULD BE PUBLIC // NEEDS Formal Arguments, LineID and Num of Trains
		void NotifyLines() ;  // Update time state for lines
		CLine*  redRoute ;  // red line - working 11/18/12
		CLine*  blueRoute ;  // blue line - started 11/18/12
		int timeCounter; //minutes
		int startHour;
		int startMinute;
		int endHour;
		int endMinute ;
		int numberOfTrains ;
		//Trains within the system -- data structure
};
#endif /* TRAINSYSTEM_H_ */

enum Line {
	RED,
	BLUE,
	INVALID
	//TRANSFER /* special case for B3 */
};  

enum eEvent {UPDATE_CLOCK, UPDATE_SIMULATION};

enum eDirection {
	INBOUND,
	OUTBOUND,
	INVALID_DIR
	//TRANSFER /* special case for B3 */
};  


// INVALID used in AddPassengersToLine, in case assignment fails

class Station;

class CLine
{

public:
	CLine(enum Line id): lineID(id), displayOn(false)
	{};

	void Initialize (TrainSystem *central);
		
	int Search(char stationType, int stationNum)
	{
		int retVal= -1 ; // return -1 if not found  // set passenger->transfer flag true

		return retVal;
	}

	void NotifyStations ();
	void AddStation (Station *toAdd) ;
	void ToggleDisplay() { displayOn= !displayOn;}
	void DisplayTrainsSnapShots(CLine*, int howMany= 3);
	void DisplayTrains(CLine*);	
	Station* getStation(int pos);
	void PlaceTrain(int pos, eDirection dir) ;
	enum Line GetLineID() {return lineID ;};
	//int getTimeToNextOutbound(int pos);
	//int getTimeToNextInbound(int pos);
	int xferPos ;

private:
	void CLine::DisplayTrainsInQueue(CLine*, int stationPos, eDirection dir, int nTrains);
	bool displayOn;
	enum Line  lineID;
	TrainSystem* central;
	LinkedList<Station> *outboundStations;
	
	//LinkedList inBoundStations;

};
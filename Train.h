/**
 * Title: Train.h
 * Date: November 7, 2012
 * Author(s): Robert O'Connor/Nick Trippel
 * Description: represents a train car as a part of the Train.
 */

#include <iostream>  // delete
using namespace std ; // delete

#ifndef TRAIN_H_
#define TRAIN_H_

class Passenger;

class Train {

	public:

		Train():etaInMinutes(0), maxCap(192){};
		virtual ~Train();
		void Initialize(int id){trainID= id;}
		void decrementETA()
		{
			etaInMinutes--;
			// cout << "id: " << trainID << endl ;  // test code - delete
		}  
		void setETA(int newVal)
		{
			etaInMinutes= newVal;
		}  
		int getETA(){return etaInMinutes;}   
		int getID() {return trainID;}
		void LoadPassengers(Queue<Passenger> *stationQ);
		
		void GetXfers(Queue<Passenger> *xferQueue);
		
		Passenger* getArrived(enum Line id, int pos);


	private:
		int maxCap ;
		int etaInMinutes;
		int trainID;
		LinkedList<Passenger> passengers ;

		//Passenger data structure

};

#endif /* TRAIN_H_ */

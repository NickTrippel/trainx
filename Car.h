/**
 * Title: Car.h
 * Date: November 7, 2012
 * Author(s): Robert O'Connor/Nick Trippel
 * Description: represents a train car as a part of the Train.
 */

#ifndef CAR_H_
#define CAR_H_

#include "Train.h"
class Passenger;
class Station;

class Car {
	public:
		Car(int,Train);
		virtual ~Car();

		/**
		 * Adds passengers to the car
		 * @param the passenger to add.
		 * @return the passenger that was added.
		 */
		void addPassenger(Passenger* );

		/**
		 * Remove a passenger from the car
		 * @param the passenger to remove
		 * @return the removed passenger
		 */
		void removePassengers(Station* destination);

		//getters (setters are not necessary).
		int getCarNumber() const;

		Train getTrain() const;

	private:
		/**
		 * The car number (1,2 or 3).
		 */
		int carNumber;
		/**
		 * The number of passengers on the train
		 */

		/**
		 * The train that is is a part of.
		 */
		Train train;

		//TODO: data structure for passengers
};

#endif /* CAR_H_ */

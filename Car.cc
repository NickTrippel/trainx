/**
 * Title: Car.cc
 * Date: November 7, 2012
 * Author(s): Robert O'Connor/Nick Trippel
 * Description: represents a train car as a part of the Train.
 */
#include "ABCList.hpp"
#include "LinkedList.hpp"
#include "Queue.hpp"
#include "Car.h"

Car::Car(int carNumber,Train train):carNumber(carNumber),train(train) {
}

Car::~Car() {
	// TODO Auto-generated destructor stub
}

int Car::getCarNumber() const {
	return this->carNumber;
}

Train Car::getTrain() const {
	return this->train;
}

void Car::addPassenger(Passenger* p) {
	//TODO: implement
}

void Car::removePassengers(Station* destination) {
	//TODO: implement
}




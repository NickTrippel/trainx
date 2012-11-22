/******************************************************************************
 Title: main.cc
 Author: Robert O'Connor
 Created on: November 5, 2012
 Description: Entry point for a train network simulation
 Usage: make (will both build and run).
 Build with: make
 Modifications:
 *******************************************************************************/
#include <iostream>
using namespace std;

#include <assert.h>
#include <string>
#include <iostream>
#include <fstream>
#include "ABCList.hpp"
#include "LinkedList.hpp"
#include "Queue.hpp"
#include "Passenger.h"
#include "Train.h"
#include "Station.h"
#include "Line.h"

#include "TrainSystem.h"

int main() {
// int main(int argc, char **argv) {
	
	
	TrainSystem* sys= new TrainSystem();
	
	sys->Start(2) ;

	system("pause") ;

	return 0;
}

/*mtrevlist based on mtrecursion12 - Spring 2012 recursion problem

NOTA BENE: Written as a stand alone function NOT a member function of the class
*/

#include <iostream>
#include <string> // added by NT based upon BB comment
#include <exception> // added by NT 
#include "ABCList.hpp"
#include "LinkedList.hpp"
using namespace std;

/* reverse the list ( DELETES it and then puts it back in REVERSE order ) */
void reverse(LinkedList<int> & theList ) 
{
	// getLength, remove, insert
	if ( theList.getLength() == 0 ) ;

	else {
		int* temp = theList.remove(1) ;
		reverse ( theList ) ;

		int lpos = theList.getLength() + 1 ;
		theList.insert(lpos, temp ) ;
	}

}

// leaves the list intact
void displayNext(LinkedList<int> & theList, int curPos = 1 ) {
		if ( curPos > theList.getLength() ) ;
		else {
			int* temp = theList.retrieve(curPos) ;
			curPos++ ;
			displayNext( theList, curPos ) ;
			cout << temp << " " ;
		}
	}



  //std::cin.clear() ;
  //std::cout << "Press ENTER to continue... " << flush;
  //std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
  //std::cin.get() ;




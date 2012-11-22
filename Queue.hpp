
/* * Queue * *  
Created on: Nov 9, 2012 *      
Author: rob *
Implementation: Nick
Implemented as a sub class of LinkedList.hpp
*/

#ifndef QUEUE_
#define QUEUE_

template <class T> 
class Queue {//: public LinkedList<T> {	
public:		
	// use default constructor
	virtual ~Queue();
	int getLength() {return aList.getLength();}
	virtual void getFront( T** qItem ) ;	
	virtual void addToFront(T* qItem) ;
	T* retrieve(int pos) ;
	virtual T* getFront( void ) ;	
	virtual void enqueue( T* qItem ) ;		
	virtual void dequeue() ;		
	virtual void dequeue( T** qItem ) ;	
	// virtual T dequeue( ) ;	// use combo of: T getFront & dequeue()
	virtual bool isEmpty();

	/*  return T ????
	// virtual T getFront( ) ;	// implemented
	virtual T enqueue( T& qItem ) ;		
	virtual T dequeue() ;		
	*/ 

private:  // declare public for testing w/ displayNext function
	LinkedList<T> aList ;

};

//template <class T> 
//Queue<T>::Queue() { };

template <class T> 
Queue<T>::~Queue() { };

template <class T> 
bool Queue<T>::isEmpty()
{
	return (aList.getLength() == 0 ) ;
}

template <class T>           // ok
void Queue<T>::getFront(T** qItem )
{
	if ( aList.isEmpty() )
		throw (-1) ;
	else
		*qItem = aList.retrieve( 1 ) ;
	// aList.retrieve( 1 , qItem ) ;
}

template <class T>           // ok
void Queue<T>::addToFront(T* qItem )
{
	aList.insert( 1, qItem ) ;
	// aList.retrieve( 1 , qItem ) ;
}

template <class T>           // ok
T* Queue<T>::getFront( )
{
	T* qItem ; 

	if ( aList.isEmpty() )
		throw (-1) ;
	else
		qItem = aList.retrieve( 1 ) ;
	// aList.retrieve( 1 , qItem ) ;

	return qItem ;
}

template <class T>            // ok
void Queue<T>::enqueue( T* qItem )
{
	aList.insert( aList.getLength() + 1 , qItem ) ;
}

template <class T>            // ok
void Queue<T>::dequeue( )
{
	if ( aList.isEmpty() )
		throw (-1) ;
	else {
		aList.remove( 1 ) ;
	}
}

template <class T>             // ok
void Queue<T>::dequeue( T** qItem )
{
	if ( aList.isEmpty() )
		throw (-1) ;
	else {
		*qItem = aList.retrieve( 1 ) ;
		aList.remove( 1 ) ;
	}
}

template <class T>
T* Queue<T>::retrieve(int pos)
{
	return aList.retrieve(pos);
}

#endif    /* QUEUE_ */


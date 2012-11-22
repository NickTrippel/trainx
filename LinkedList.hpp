/*
 *
 * Assignment 2, C.Sci 235. Fall 2012 
 *		- LinkedList ADT combined specification and implementation File
 *
 * Author: Kenneth "Nick" Trippel
 *
 * Date: Oct. 07, 2012
 *
 */

/* ADT list - Pointer-based implementation. 
   Portions of this are based on code from Frank M. Carrano, 
   Data Abstraction & Problem Solving with C++, 5th Edition.
 */


/** @file LinkedList.hpp */

#ifndef CS235_LINKEDLIST_HPP
#define CS235_LINKEDLIST_HPP

#include <exception>   // for exceptions
#include <cstddef>     // for NULL
#include <new>         // for bad_alloc

using namespace std;

/** @class LinkedList
* ADT list - Pointer-based specification. */

template <class T> 
class LinkedList : public ABCList<T>
{
public:
	// Constructors and destructor:

	/** Default constructor. */
	LinkedList();

	/** Destructor. */
	~LinkedList();

	// LinkedList operations:
	virtual bool isEmpty() ;
	virtual int getLength() ;
	virtual void insert(int pos,  T* item) ;	
	virtual void add(T* item) 
	{ 
		insert(getLength() + 1, item) ;
	} ;	
	virtual T* remove(int pos) ;				
	virtual T* retrieve(int pos)  ;

	virtual void display(  ) {
		ListNode *cur = head ;
		if ( cur == NULL ) 
			return ;
		while ( cur != NULL ) {
			//cout << cur->item << " " ;	
			cur = cur->next ;
		}
	}

	//virtual void displayBackwards(  ) {
	//	if (this->getLength() == 0 ) ;
	//	else {
	//		// int temp = this->retrieve(1) << " " ;	
	//		T temp = this->remove(1) ;
	//		displayBackwards() ;
	//		//cout << temp << " " ;
	//	}
	//}

	/** A node on the list. */
	struct ListNode
	{
		/** A data item on the list. */
		T* item;
		/** Pointer to next node. */
		ListNode    *next;
	}; // end ListNode

private:

	/** Number of items in list. */
	int       size;
	/** Pointer to linked list of items. */
	ListNode *head;

	/** Locates a specified node in a linked list.
	* @pre pos is the number of the desired node.
	* @post None.
	* @param pos The index position of the node to locate.
	* @return A pointer to the pos index-th node. If pos < 1
	*         or pos > the number of nodes in the list,
	*         returns NULL. */
	ListNode *find(int pos) ;

}; // end List
// End of header



/** ADT list - Pointer-based implementation. */

// definitions of methods follow:

template <class T> 
LinkedList<T>::LinkedList(): size(0)
{
	head= NULL ;
}

template <class T> 
LinkedList<T>::~LinkedList()
{
	while (!isEmpty()) {
		// cout << head->item << endl ;  // enable to check that dtor is working
		// previous line assumes << is overloaded to work with T item
		remove(1);
	}
}  // end destructor

template <class T> 
bool LinkedList<T>::isEmpty() 
{
	return size == 0;
}  // end isEmpty

template <class T> 
int LinkedList<T>::getLength() 
{
	return size;
}  // end getLength

template <class T> 
typename LinkedList<T>::ListNode * LinkedList<T>::find(int pos) 
   //    LinkedList<T>::ListNode *LinkedList<T>::find(int pos)  // this was causing problems
{
	if ( (pos < 1) || (pos > getLength()) )
		return NULL;

	else  // count from the beginning of the list.
	{  ListNode *cur = head;
	for (int skip = 1; skip < pos; ++skip)
		cur = cur->next;
	return cur;
	}  // end if
}  // end find

template <class T> 
T* LinkedList<T>::retrieve(int pos) 
{
	T* dataItem ;

	if ( (pos < 1) || (pos > getLength()) )
		throw (-1) ;
	else
	{  // get pointer to node, then data in node
		ListNode *cur = find(pos);
		dataItem = cur->item;
	}  // end if

	return dataItem ;

}  // end retrieve

template <class T> 
void LinkedList<T>::insert(int pos,  T* item)  
{
	int newLength = getLength() + 1;

	if ( (pos < 1) || (pos > newLength) )
		throw (-1) ;
	else
	{  // try to create new node and place newItem in it
		try
		{
			ListNode *newPtr = new ListNode;
			size = newLength;
			newPtr->item = item ;

			// attach new node to list
			if (pos == 1)
			{  // insert new node at beginning of list
				newPtr->next = head;
				head = newPtr;
			}
			else
			{  ListNode *prev = find(pos-1);
			// insert new node after node
			// to which prev points
			newPtr->next = prev->next;
			prev->next = newPtr;
			}  // end if
		}  // end try
		catch (bad_alloc e)
		{
			throw (-1) ;
		}  // end catch
	}  // end if
}  // end insert

template <class T> 
T* LinkedList<T>::remove(int pos) 
{
	ListNode *cur;
	T* dataItem ;

	if ( (pos < 1) || (pos > getLength()) )
		throw (-1) ;
	else
	{  --size;
	if (pos == 1)
	{  // delete the first node from the list
		cur = head;  // save pointer to node
		head = head->next;
		dataItem = cur->item; 
	}

	else
	{  ListNode *prev = find(pos - 1);
	// delete the node after the node to which prev points
	cur = prev->next;  // save pointer to node
	prev->next = cur->next;
	dataItem = cur->item;  
	}  // end if

	// return node to system

	cur->next = NULL;
	delete cur;
	cur = NULL;
	}  // end if

	return dataItem ;

}  // end remove

#endif



#ifndef _CS235_ABCLIST_H_
#define _CS235_ABCLIST_H_


template <class T>
class ABCList {
public:
	virtual bool isEmpty () = 0;
	virtual int  getLength () = 0;
	virtual void insert (int pos, T* item) = 0;
	virtual T*    remove (int pos) = 0;
	virtual T*    retrieve (int pos) = 0;
	virtual void display() = 0 ; // Added by Nick for recursion
	virtual ~ABCList() { } ;  // ADDED BY NICK!!!
};

#endif



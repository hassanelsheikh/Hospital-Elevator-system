#pragma once
#include "Node.h"

template <typename T>
class PriorityQueue
{
private:

	Node<T>* backPtr;
	Node<T>* frontPtr;
public:
	PriorityQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool enqueueElev(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peekFront(T& frntEntry)  const;
	void PrintQueue();
	T* toArray(int& count);	//returns array of T (array if items)
	~PriorityQueue();
};


template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;

}


template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
	if (frontPtr == nullptr)
		return true;
	else
		return false;
}


/*Function:enqueue
Adds newEntry according to its priority.
Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool PriorityQueue<T>::enqueue(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	newNodePtr->setPriority(newEntry);
	// Insert the new node
	if (isEmpty()) // The Priorityqueue is empty
	{
		frontPtr = newNodePtr;
		backPtr = newNodePtr;
		return true;
	}
	else if (newNodePtr->getPriority() > frontPtr->getPriority())  //new node has higher priority than first node
	{
		newNodePtr->setNext(frontPtr);
		frontPtr = newNodePtr;
		return true;
	}
	else
	{
		Node<T>* ptr = frontPtr;
		while (ptr!= NULL && ptr->getPriority() >= newNodePtr->getPriority())
		{
			if (ptr->getNext() == NULL) {
				newNodePtr->setNext(ptr->getNext());
				ptr->setNext(newNodePtr);
				return true;
			}
			else if (ptr->getNext()->getPriority() < newNodePtr->getPriority())
			{
				newNodePtr->setNext(ptr->getNext());
				ptr->setNext(newNodePtr);
				return true;
			}
			else
			{
				ptr = ptr->getNext();
			}
			
		}
	}
} // end enqueue

template <typename T>
bool PriorityQueue<T>::enqueueElev(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	newNodePtr->setPriorityelev(newEntry);
	// Insert the new node
	if (isEmpty()) // The Priorityqueue is empty
	{
		frontPtr = newNodePtr;
		backPtr = newNodePtr;
		return true;
	}
	else if (newNodePtr->getPriority() > frontPtr->getPriority())  //new node has higher priority than first node
	{
		newNodePtr->setNext(frontPtr);
		frontPtr = newNodePtr;
		return true;
	}
	else
	{
		Node<T>* ptr = frontPtr;
		while (ptr!= NULL && ptr->getPriority() >= newNodePtr->getPriority())
		{
			if (ptr->getNext() == NULL) {
				newNodePtr->setNext(ptr->getNext());
				ptr->setNext(newNodePtr);
				return true;
			}
			else if (ptr->getNext()->getPriority() < newNodePtr->getPriority())
			{
				newNodePtr->setNext(ptr->getNext());
				ptr->setNext(newNodePtr);
				return true;
			}
			else
			{
				ptr = ptr->getNext();
			}
			
		}
	}
} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.
Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool PriorityQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr;

	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;


	return true;

}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peekFront
gets the front of this queue. The operation does not modify the queue.
Input: None.
Output: The front of the queue.
return: flase if Queue is empty
*/
template <typename T>
bool PriorityQueue<T>::peekFront(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
template<typename T>
inline void PriorityQueue<T>::PrintQueue()
{
	PriorityQueue temp;
	Pickable* p;
	while (peekFront(p)) {
		dequeue(p);
		if (temp.isEmpty())
		{
			cout << p->getID();
		}
		else
		{
			cout << ", " << p->getID();
		}
		temp.enqueue(p);
	}
	while (temp.peekFront(p)) {
		temp.dequeue(p);
		enqueue(p);
	}
}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
}

/////////////////////////////////////////////////////////////////////////////////////////




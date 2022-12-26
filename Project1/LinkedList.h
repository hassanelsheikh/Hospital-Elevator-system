
#ifndef _LINKEDLIST
#define _LINKEDLIST
#include<iostream>
#include "Node.h"
using namespace std;

class Events;
class Floor;

template <typename T>
class LinkedList
{
private:
	Node<T>* Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
public:


	LinkedList()
	{
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/

	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;

	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}



	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T& data)
	{
		Node<T>* P = Head;
		Node<T>* R = new Node<T>(data);

		if (Head == nullptr)
		{
			Head = R;
			return;
		}



		while (P->getNext())
			P = P->getNext();

		P->setNext(R);

		return;
	}



	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	T Find(T Key)
	{
		Node<T>* P = Head;
		while (P)
		{
			if (P == Key)
			{
				return P;
			}
			P = P->getNext();
		}
		return;

	}


	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T& value)
	{
		int Count = 0;
		Node<T>* P = Head;
		while (P)
		{
			if (P->getItem() == value)
			{
				Count++;

			}
			P = P->getNext();
		}


		return Count;
	}



	//[4] DeleteFirst
	//Deletes the first node in the list
	void DeleteFirst()
	{
		Node<T>* P = Head;

		if (Head)
		{
			Head = P->getNext();
			delete P;
			return;
		}
		return;

	}



	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast()
	{
		Node<T>* P = Head;
		if (!P)
		{
			return;
		}
		while (P->getNext())
		{
			if ((P->getNext()->getNext()) == nullptr)
			{
				Node <T>* R = P->getNext();
				P->setNext(nullptr);
				delete R;
				return;
			}
			P = P->getNext();
		}
		Head = nullptr;
		delete P;
		return;


	}


	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const T& value)
	{
		Node<T>* P = Head;


		while (P)
		{
		
			if (P->getItem() == value)
			{
				Head = P->getNext();
				delete P;
				//cout << "Now the list is empty" << endl;
				return true;
			}
			if (P->getNext()->getItem() == value)
			{
				Node <T>* R = P->getNext();
				P->setNext(R->getNext());
				delete R;
				return true;
			}
			P = P->getNext();
		}

		return false;

	}


	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T& value)
	{
		Node<T>* P = Head;


		while (P)
		{
	
			if (P->getItem() == value)
			{
				Head = P->getNext();
				delete P;

			}
			if (P->getNext()->getItem() == value)
			{
				Node <T>* R = P->getNext();
				P->setNext(R->getNext());
				delete R;

			}
			P = P->getNext();
		}

		return false;
	}




	//[9] GetPickableFromID
	//Returns the Pickable from its ID
	Pickable* GetPickableFromID(int& ID)
	{
		Node<T>* SearchPickable = Head;

		while (SearchPickable)
		{
			if (SearchPickable->getItem()->getID() == ID)
			{
				return SearchPickable->getItem();
			}
			SearchPickable = SearchPickable->getNext();
		}
		return nullptr;
	}

	//[10] PrintList
	void PrintList()	const //to Print UP and Downs
	{
		Node<T>* p = Head;

		/*if (IsEmpty()) return;*/

		while (p)
		{
			if (p->getNext() == NULL)
			{
				cout << p->getItem()->getID();
			}
			if (p->getNext() != NULL)
			{
				cout << p->getItem()-> getID() << ", ";
			}
			p = p->getNext();
		}

	}

	//[11] IsEmpty

	bool IsEmpty()
	{
		if (Head == nullptr)
			return true;
		else
			return false;

	}

	//[12] get first node in the List 
	bool GetfirstNode(T& Pick)
	{
		if (Head == nullptr)
			return false;
		else
		{
			Node<T>* tempPtr = Head;
			Pick = Head->getItem();
			return true;
		}
	}

	//[13] Gets the event with ET to check if its equal timestamp
	bool getEventByET(int t ,T& p)
	{
		Node<T>* temp = Head;
		while (temp)
		{
			if (temp->getItem()->getET() == t)
			{
				p = temp->getItem();
				return true ;
			}
			temp = temp->getNext();
		}
		return false;
	}

	//Get Floor by Source
	Floor* getFloorbySRC(int src)
	{
		Node<T>* SearchFloor = Head;
		while (SearchFloor)
		{
			if (SearchFloor->getItem()->getf() == src)
			{
				return SearchFloor->getItem();
			}
			SearchFloor = SearchFloor->getNext();
		}
	}
	bool checkstairs(int t, int S, T& pick) {
		Node<T>* temp = Head;
		Pickable* p;
		while (temp) {
			p = temp->getItem();
			int src = p->getsrc();
			int trg = p->gettrg();
			int numfloor = trg - src;
			if (t - (p->getstairtime()) == (abs(numfloor) * S)) {
				pick = p;
				return true;
			}
			temp = temp->getNext();
		}
		return false;
	}

	bool checkAutoS(int t, int AutoS,T& pick) {
		Node<T>* temp = Head;
		Pickable* p;
		while (temp) {
			p = temp->getItem();
			if ((t - p->getTime()) == AutoS) {
				pick = p;
				return true;
			}
			temp = temp->getNext();
		}
		return false;
	}

	//get next
	bool getNextoF(Pickable *pHos)
	{
		Node<T>* temp = Head;
		while (temp)
		{
			if (temp->getItem() == pHos)
			{
				pHos = temp->getNext()->getItem();
				return true;
			}
			temp = temp->getNext();
		}
		return false;
	}
};

#endif	

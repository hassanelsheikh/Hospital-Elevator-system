
#ifndef  LBAG
#define  LBAG
using namespace std;
#include "Node.h"
template <typename T>
class ListBag
{
	Node<T>* Head;	//Pointer to the head of the list
public:

	ListBag()  //constructor
	{
		Head = nullptr;
	}

	~ListBag()  //destructor
	{
		DeleteAll();
	}

	void DeleteAll()        // delete all items in the bag
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}


	void AddNode(T it)   // Add item in the bag
	{
		Node<T>* nptr = new Node <T>(it);
		//nptr->setItem(it);
		if (Head == nullptr)
			Head = nptr;
		else
		{
			nptr->setNext(Head);
			Head = nptr;
		}
		return;
	}


	bool RemoveNode(T it)   //Remove item from the bag
	{
		Node<T>* ptr = Head;
		while (ptr)
		{
			if (ptr->getItem() == it)
			{
				ptr->setItem(Head->getItem());
				Node<T>* temp = Head;
				Head = Head->getNext();
				delete temp;
				return true;
			}
			else
				ptr = ptr->getNext();
		}
		return false;
	}

	bool IsEmpty()  // check if the bag id empty or not
	{
		if (Head == nullptr)
			return true;
		else
			return false;

	}


	T Find(T Key)   //search for a certain item in the bag
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




};




#endif

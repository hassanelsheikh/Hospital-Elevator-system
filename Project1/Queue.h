#pragma once
#include <iostream>
#include "Node.h"
using namespace std;

template <class T>
class Queue {

	Node<T>* Fptr;
	Node<T>* Bptr;
	int count;

public:
	Queue()
	{
		Fptr = nullptr;
		Bptr = nullptr;
		count = 0;
	}
	bool IsEmpty()  const
	{
		if (Fptr == NULL) return true;
		else return false;
	}
	bool enqueue(const T& nData);
	bool dequeue(T& Fdata);
	bool peek(T& Fdata) const;
	void PrintQueue();
	int getSize() const;
	Queue(const Queue<T>& LQ);
	~Queue();

};
template<class T>
bool Queue<T>::enqueue(const T& nData)
{
	Node<T>* newNode = new Node<T>(nData);
	if (IsEmpty())
	{
		Fptr = newNode;
		Bptr = newNode;
	}
	else
	{
		Bptr->setNext(newNode);
		newNode->setNext(nullptr);
		Bptr = newNode;
	}
	count++;
	return true;
}
template<class T>
bool Queue<T>::dequeue(T& Fdata)
{

	if (IsEmpty())
	{
		return false;
	}
	Node<T>* oldHead = Fptr;
	Fdata = oldHead->getItem();
	Fptr = Fptr->getNext();

	delete oldHead;
	count--;
	return true;
}

template <typename T>
bool Queue<T>::peek(T& Fdata) const
{
	if (IsEmpty())
		return false;

	Fdata = Fptr->getItem();
	return true;

}
template <class T>
Queue<T>::~Queue()
{
	T temp;
	while (dequeue(temp));
}

template <class T>
int Queue<T>::getSize()const
{
	return count;
}

template <class T>
void Queue<T>::PrintQueue()
{
	Queue temp;
	Pickable* p;
	while (peek(p)) {
		dequeue(p);
		if (temp.IsEmpty())
		{
			cout << p->getID();
		}
		else
		{
			cout << ", " << p->getID();
		}
		temp.enqueue(p);
	}
	while (temp.peek(p)) {
		temp.dequeue(p);
		enqueue(p);
	}
}

template <typename T>
Queue<T>::Queue(const Queue<T>& LQ)
{
	Node<T>* NodePtr = LQ.Fptr;
	if (!NodePtr) //LQ is empty
	{
		Fptr = Bptr = nullptr;
		return;
	}

	//insert the first node
	Node<T>* ptr = new Node<T>(NodePtr->getItem());
	Fptr = Bptr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		Bptr->setNext(ptr);
		Bptr = ptr;
		NodePtr = NodePtr->getNext();
	}
}
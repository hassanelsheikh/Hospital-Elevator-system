#ifndef __NODE_H_
#define __NODE_H_
#include"Pickable.h"
class Pickable;

template <typename T>


class Node

{
private:
	T item; // A data item
	Node<T>* next; // Pointer to next node
	int Priority;
public:
	Node();
	Node(const T& r_Item);	//passing by const ref.
	Node(const T& r_Item, Node<T>* nextNodePtr);
	//Node(const T& r_Item, const int& pr);
	void setItem(const T& r_Item);
	void setNext(Node<T>* nextNodePtr);
	T getItem() const;
	Node<T>* getNext() const;
	void setPriority(Pickable* o);
	int getPriority();
	void setPriorityelev(Pickable* o);
	void Get_next_of();
}; // end Node


template < typename T>
Node<T>::Node()
{
	next = nullptr;
}

template < typename T>
Node<T>::Node(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
}

template < typename T>
Node<T>::Node(const T& r_Item, Node<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}


template < typename T>
void Node<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
T Node<T>::getItem() const
{
	return item;
}

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
}

template < typename T>
void Node<T>::setPriority(Pickable* o)
{
	Priority = o->getEmr();
}


template < typename T>
int Node<T>::getPriority()
{
	return Priority;
}
template<typename T>
void Node<T>::setPriorityelev(Pickable* o)
{
	if (o->getsrc() < o->gettrg()) {
		Priority = (o->getsrc()) - (o->gettrg());
	}
	if (o->getsrc() > o->gettrg()) {
		Priority = (o->gettrg()) - (o->getsrc());
	}
}
template < typename T>
void Node<T>::Get_next_of()
{
	if (this)
	{
		this = this->getNext();
	}
}

#endif
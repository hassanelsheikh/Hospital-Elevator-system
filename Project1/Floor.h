#pragma once
#include"priorityQueue.h"
#include"Queue.h"
#include"LinkedList.h"
#include "Pickable.h"
#include "Elevator.h"
#include "Hospital.h"

class Floor
{
private:
	int pwait;
	int cwait;
	int vwait;
	int f;
	//PriorityQueue<Pickable*> patients;
	//Queue<Pickable*> cargo;
	//LinkedList<Pickable*> visitors;
	PriorityQueue<Pickable*> PidUP;
	PriorityQueue<Pickable*> PidDown;
	LinkedList<Pickable*> VidUP;
	LinkedList<Pickable*> VidDown;
	Queue<Pickable*> CidUP;
	Queue<Pickable*> CidDown;
public:
	Floor();
	Floor(int x);
	void incpwait(Pickable* p);
	void incvwait(Pickable* p);
	void inccwait(Pickable* p);
	void printPidUp();
	void printPidDown();
	void printVidUp();
	void printVidDown();
	void printCidUp();
	void printCidDown();
	Pickable* decpwaitUP();
	Pickable* decpwaitDown();
	Pickable* decvwaitUP();
	Pickable* decvwaitDown();
	Pickable* deccwaitUP();
	Pickable* deccwaitDown();

	//this function returns true as long as there are requests
	bool checkpWait();
	bool checkcWait();
	bool checkvWait();
	bool ispidUpEmpty();
	bool ispidDownEmpty();
	bool isVidUPEmpty();
	bool isVidDownEmpty();
	bool isCidUPEmpty();
	bool isCidDownEmpty();
	int getpwait();
	int getvwait();
	int getcwait();
	int getf();
	bool AutoStairsUp(int t, int autos, Pickable*& pick);
	
	bool AutoStairsDown(int t, int autos, Pickable*& pick);
	//search for visitor in the floor and returns true if found and deleted
	bool delVisByID(int id, Pickable* &pick);
	Pickable* decpatients();
	Pickable* decvisitors();
	Pickable* deccargo();
	Pickable* getPickable(int id);
};


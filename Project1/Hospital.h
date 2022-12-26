#pragma once
#include"Elevator.h"
#include"LinkedList.h"
#include"ListBag.h"
#include"UI.h"
#include"Events.h"
#include<fstream>
#include"priorityQueue.h"
#include"Queue.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include"Floor.h"
#include"Node.h"
#include<dos.h>

using namespace std;

class UI;
class Hospital
{
private:
	//PriorityQueue<Pickable*> patients;
	LinkedList<Floor*> floors_List;
	Queue<Events*> events;
	//LinkedList<Pickable*> visitors;
	//Queue<Pickable*> cargo;
	LinkedList<Pickable*> stairsL;
	LinkedList<Pickable*> completed;
	Elevator pElev;
	Elevator vElev;
	Elevator cElev;
	int timestep;
	int Twait;
	int Tcomp;
	int Tleft;
	int maxET;
	int inser;
	int stair;
	int Emove;
	int NumOfFloor;
	ifstream cfile;
	ofstream outfile;
public:
	Hospital();
	void setdel(int d);
	void setwait(int wait);
	void settimestep(int t);
	void createfloor(int& f);
	int getdel();
	int getwait();
	int getcomp();
	int gettimestep();
	int getTleft();
	int getInService();
	int getstair();
	int getNumOfFloors();

	bool checlavail(int id);
	int PrintWait_P(int floor);
	int PrintWait_V(int floor);
	int PrintWait_C(int floor);


	//void PrintDeliv_P();
	//void PrintDeliv_V();
	//void PrintDeliv_C();
	void setNumOfFloors(int f);
	void PrintPIdUp(int f);
	void PrintPIdDown(int f);

	void PrintVisUp(int f);
	void PrintVisDown(int f);

	void PrintCIdUp(int f);
	void PrintCIdDown(int f);
	void printelevPstat();
	void printelevVstat();
	void printelevCstat();

	void setEcap(Elevator* elev, int c);
	void AddtoQueue(Pickable * pick); //to add pass/cargo to queue
	bool DeletePass(int ID); //to Delete an pass/cargo
	void AddPicktoElev(int numf);
	bool checkIfValid(Elev_TYPE t,Pickable* p);

	//function to move elevator
	/*void moveElevator()*/


	void simulate();
	void InteractiveMode(UI* p);
	void SilentMode(UI* p);
	void StepByStepMode(UI* p);
	void getinfo(int& Floor, int& VES, int& PES, int& CES, int& VEC, int& PEC, int& CEC, int& S, int& AutoS, int& E);
	void executeEvents();
	void takestairsByVis(int ID);
	bool outputfile();
	void checkForrequests(int nfloor);

	void printInElev(Elev_TYPE t);
};

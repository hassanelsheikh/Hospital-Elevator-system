#pragma once
#include "defs.h"
#include <iostream>
using namespace std;

class Pickable
{
private:
	int arrivalTime;
	Pick_Type Ptype;
	int sourceFloor;
	int targetFloor;
	int emrLevel;
	int ID;
	int stairtime;
	PICK_STATUS status;

public:
	//constructors
	Pickable(int id, Pick_Type type);

	/*Pickable(int id, Pick_Type type, int src, int trg, int arriveTime);*/
	Pickable(int id, Pick_Type type, int src, int trg, int arriveTime);

	//for patients only
	Pickable(int id, Pick_Type type, int src, int trg, int arriveTime, int emrlvl);
	
	//setters
	void setID(int id);
	void setPType(Pick_Type type);
	void setArrivaltime(int t);
	void setSrc(int src);
	void setTrg(int trg);
	void setEmrlvl(int lvl);
	void setStatus(PICK_STATUS s);
	void setstairtime(int t);

	//getters
	int getID();
	Pick_Type getType();
	PICK_STATUS getStatus();
	int getsrc();
	int gettrg();
	int getEmr();
	int getTime();
	int getstairtime();


};


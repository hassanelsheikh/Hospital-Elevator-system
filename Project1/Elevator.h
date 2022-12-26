#pragma once
#include "defs.h"
#include"priorityQueue.h"
#include "Pickable.h"



class Elevator
{
private:
	//elevator type (patient, visitors, cargos)
	Elev_TYPE Etype; 

	PriorityQueue<Pickable*> inElev;

	//elevator capacity
	int Ecapacity;

	//elevator speed
	int speed;

	//checkup to see if out of service or not
	int checkupPeriod;

	//elevator state (idle, move, unload, avail, out)
	ELEV_STATUS estate;

	int eFloor;

	int eTrg;

	int currCapacity;

	//max target in elevator
	int maxIn;
	int minIn;
	//max target out elevator
	int maxOut;
	int minOut;

	int tIdle;

public:
	Elevator();
	Elevator(Elev_TYPE t, ELEV_STATUS s, int spd, int c);

	//setters
	void setType(Elev_TYPE t);
	void setSpeed(int s);
	void setCheckuptime(int t);
	void setCapacity(int cp);
	void setEstate(ELEV_STATUS st);
	void seteTrg(int trg);

	//MaxIn and MaxOut, compare them to eTrg and sets max
	void setMaxIn(int m);
	void setMaxOut(int o);
	void setMinIn(int m);
	void setMinOut(int m);
	void AddToElevList(Pickable* pick);
	Pickable* peekload();
	void settIdle(int l);

	//function to increment tIdle to check if it reached 3 timesteps to reset to Available
	void inctIdle();
	
	//function to increment or decrement elevator floor
	void moveElevUp();
	void moveElevDown();

	//getters
	Elev_TYPE getType() const;
	int getSpeed();
	int getCheckuptime();
	int getCapacity();
	int getCurrCapacity();
	ELEV_STATUS getEstate();
	int geteFloor();
	int geteTrg();
	int getMaxIn();
	int getMaxOut();
	int gettIdle();
	bool isEmpty();
	bool checkFull();
	void printElevList();





	

};


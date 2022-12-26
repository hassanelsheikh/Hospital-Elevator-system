#pragma once
#include "Events.h"

class Arrival : public Events 
{
	Pick_Type pickType;
	int ET; //event time step
	int ID; 
	int src;
	int trg;
	int emr_level; //patients only
	char Type;

public:
	Arrival(int& id, int& et, int& source, int& target, Pick_Type& type , char& e);
	Arrival(int& id, int& et, int& source, int& target, Pick_Type& type, int& emr, char& e);
	virtual void Execute(Hospital* hos);
//	//constructor
//	Arrival();
//	Arrival(int id, int et, int source, int target, char type, Hospital* hos);
//
//	// this if for patients only

//
//
//	//setters
void setType(char type);
void setET(int et);
void setID(int id);
void setSrc(int source);
void setTrg(int target);
void setEmr(int level);
//
//	//getters
//	int getET() const;
//	int getID() const;
//	int getSrc();
//	int getTrg();
//	int getEmr();



};


#pragma once
#include "defs.h"


class Hospital;
class Events {
protected:
	int ID;
	int ET;
	char Type;

public:
	//Implement get id, get et in main event rather than implementing them in each event
	Events(int id, int t, char e);
	Events();
	virtual int getET();
	virtual int getPickableID();
	virtual char gettype();
	virtual void Execute(Hospital* hos) = 0;
};
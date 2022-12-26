#pragma once
#include "Events.h"
#include "defs.h"

class Stairs : public Events
{
	int ET;
	int ID;
	char Type;

public:

	Stairs(int& time, int& id, char e);
	virtual void Execute(Hospital* hos);
	int getET();

};




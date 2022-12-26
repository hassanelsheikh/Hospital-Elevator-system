#pragma once
#include "Events.h"

class Leave : public Events
{
private:
	Pick_Type* Ptype;
	char e;
public:
	Leave(int time, int ID, char e);
	virtual void Execute(Hospital* hos);
};


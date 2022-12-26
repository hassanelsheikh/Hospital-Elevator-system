#include "Arrival.h"
#include"Hospital.h"



Arrival::Arrival(int& id, int& et, int& source, int& target, Pick_Type& type, char& e) : Events(id, et, e)
{
	pickType = type;
	ID = id;
	ET = et;
	src = source;
	trg = target;
	Type = e;
}





//patient
Arrival::Arrival(int& id, int& et, int& source, int& target, Pick_Type& type, int& emr, char& e) : Events(id, et,e)
{
	pickType = type;
	ID = id;
	ET = et;
	src = source;
	trg = target;
	emr_level = emr;
	Type = e;
}

void Arrival::Execute(Hospital* hos)
{
	Pickable* pick = new Pickable(ID, pickType, src, trg, /*--->>>>re*/ET);
	if (pick->getType() == TYPE_PTNT) //set emr if patient
	{
		pick->setEmrlvl(emr_level);
	}
	hos->AddtoQueue(pick);
	int x = hos->getwait();
	x++; // increment timestep
	hos->setwait(x);
}
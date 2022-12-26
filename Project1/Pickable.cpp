#include "Pickable.h"
#include "Hospital.h"

Pickable::Pickable(int id, Pick_Type type)
{
	ID = id;
	Ptype = type;
	status = WAITING;
}



Pickable::Pickable(int id, Pick_Type type, int src, int trg, int arriveTime)
{
	ID = id;
	Ptype = type;
	sourceFloor = src;
	targetFloor = trg;
	arrivalTime = arriveTime;
	status = WAITING;
}

//for patient only
Pickable::Pickable(int id, Pick_Type type, int src, int trg, int arriveTime, int emrlvl)
{
	ID = id;
	Ptype = type;
	sourceFloor = src;
	targetFloor = trg;
	arrivalTime = arriveTime;
	emrLevel = emrlvl;
	status = WAITING;
}

void Pickable::setID(int id) 
{ 
	ID = id; 
}

void Pickable :: setPType(Pick_Type type)
{
	Ptype = type;
}

void Pickable::setSrc(int s) 
{
	sourceFloor = s;
}

void Pickable::setTrg(int t)
{
	targetFloor = t;
}

void Pickable::setEmrlvl(int l) 
{
	emrLevel = l;
}

void Pickable::setArrivaltime(int t)
{
	arrivalTime = t;
}

void Pickable::setStatus(PICK_STATUS s)
{
	status = s;
}

void Pickable::setstairtime(int t)
{
	stairtime = t;
}

int Pickable::getID() { return ID; }

Pick_Type Pickable ::getType() { return Ptype; }

int Pickable::getsrc() { return sourceFloor; }

int Pickable::gettrg() { return targetFloor; }

int Pickable::getTime() { return arrivalTime; }

int Pickable::getstairtime()
{
	return stairtime;
}

int Pickable::getEmr() { return emrLevel; }

PICK_STATUS Pickable::getStatus() { return status; }


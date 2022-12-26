#include "Stairs.h"
#include"Hospital.h"

Stairs::Stairs(int& time, int& id, char e) : Events(id,time,e)
{
	ET = time;
	ID = id;
	Type = e;
}
void Stairs::Execute(Hospital* hos) {
	hos->takestairsByVis(getPickableID());
}

int Stairs::getET()
{
	return ET;
}

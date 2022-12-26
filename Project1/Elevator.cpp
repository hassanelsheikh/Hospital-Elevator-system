#include "Elevator.h"
#include "Hospital.h"

Elevator::Elevator()
{
	eFloor = 0;
	estate = IDLE;
	currCapacity = 0;
	eTrg = -1;
	tIdle = 0;
}

Elevator :: Elevator(Elev_TYPE t, ELEV_STATUS s, int spd, int c)
{
	Etype = t;
	estate = s;
	speed = spd;
	Ecapacity = c;
	eFloor = 0;
	currCapacity = 0;
	eTrg = -1;
	tIdle = 0;
}

//setters

void Elevator::setType(Elev_TYPE t)
{
	Etype = t;
}

void Elevator::setSpeed(int s)
{
	speed = s;
}

void Elevator :: setCheckuptime(int t)
{
	checkupPeriod = t;
}
void Elevator :: setCapacity(int cp)
{
	Ecapacity = cp;
}

void Elevator::setEstate(ELEV_STATUS st)
{
	estate = st;
}

void Elevator::seteTrg(int trg)
{
	eTrg = trg;
}

void Elevator::setMaxIn(int m)
{
	maxIn = m;
	if (maxIn >= maxOut)
	{
		eTrg = maxIn;
	}
}

void Elevator::setMaxOut(int o)
{
	maxOut = o;
	if (maxOut >= maxIn)
	{
		eTrg = maxOut;
	}
}

void Elevator::setMinIn(int m)
{
	minIn = m;
	if (minIn <= minOut)
	{
		eTrg = minIn;
	}
}

void Elevator::setMinOut(int m)
{
	minOut = m;
	if (minOut <= minIn)
	{
		eTrg = minOut;
	}
}

void Elevator::AddToElevList(Pickable* pick)
{
	inElev.enqueueElev(pick);
	currCapacity++;
}

Pickable* Elevator::peekload()
{
	Pickable* p;
	inElev.peekFront(p);
	return p;
}

void Elevator::settIdle(int l)
{
	tIdle = l;
}

void Elevator::inctIdle()
{
	tIdle++;
}

void Elevator::moveElevUp()
{
	eFloor++;
}

void Elevator::moveElevDown()
{
	eFloor--;
}


//getters
Elev_TYPE Elevator::getType() const
{
	return Etype;
}

int Elevator::getSpeed()
{
	return speed;
}

int Elevator::getCheckuptime()
{
	return checkupPeriod;
}

int Elevator::getCapacity()
{
	return Ecapacity;
}

int Elevator::getCurrCapacity()
{
	return currCapacity;
}

ELEV_STATUS Elevator::getEstate()
{
	return estate;
}

int Elevator::geteFloor()
{
	return eFloor;
}

int Elevator::geteTrg()
{
	return eTrg;
}

int Elevator::getMaxIn()
{
	return maxIn;
}

int Elevator::getMaxOut()
{
	return maxOut;
}

int Elevator::gettIdle()
{
	return tIdle;
}

bool Elevator::isEmpty()
{
	if(currCapacity == 0)
	{
		return true;
	}
	else {
		return false;
	}
}

bool Elevator::checkFull()
{
	if (currCapacity == Ecapacity) {
		return true;
	}
	else {
		return false;
	}
}

void Elevator::printElevList()
{
	inElev.PrintQueue();
}

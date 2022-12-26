#include "Events.h"
Events::Events(int id, int t ,char e)
{
	ID = id;
	ET = t;
	Type = e;
}

int Events::getET()
{
	return ET;
}

int Events::getPickableID()
{
	return ID;
}
char Events::gettype()
{
	return Type;
}
Events::Events() {

}
#include "Leave.h"
#include "Hospital.h"


Leave::Leave(int time, int id , char e) : Events(id, time ,e)
{
}


void Leave::Execute(Hospital* hos)
{
	hos->DeletePass(getPickableID());
}
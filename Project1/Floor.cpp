#include "Floor.h"
#include "Hospital.h"

Floor::Floor()
{
	 pwait = 0;
	 cwait = 0;
	 vwait = 0;
}

Floor::Floor(int x) {
	pwait = 0;
	cwait = 0;
	vwait = 0;
	f = x;
}

//Adds patient to floor list and increment wait
void Floor :: incpwait(Pickable* p) 
{
	pwait++;
	//patients.enqueue(p);
	if (p->gettrg() > p->getsrc())
	{
		PidUP.enqueue(p);
	}
	else
	{
		PidDown.enqueue(p);
	}
}

//Adds visitor to floor list and increment wait
void Floor::incvwait(Pickable* v) {
	vwait++;
	//visitors.InsertEnd(v);
	if (v->gettrg() > v->getsrc())
	{
		VidUP.InsertEnd(v);
	}
	else
	{
		VidDown.InsertEnd(v);
	}
}

//Adds cargo to floor list and increment wait
void Floor::inccwait(Pickable* c) {
	cwait++;
	if (c->gettrg() > c->getsrc())
	{
		CidUP.enqueue(c);
	}
	else
	{
		CidDown.enqueue(c);
	}
}
void Floor::printPidUp()
{
	//PriorityQueue<Pickable*> temp;
	//Pickable* p;
	//while (PidUP.peekFront(p)) {
	//	PidUP.dequeue(p);
	//	temp.enqueue(p);
	//}
	//while (temp.peekFront(p)) {
	//	temp.dequeue(p);
	//	cout <<" "<< p->getID() << ",";
	//	PidUP.enqueue(p);
	//}
	PidUP.PrintQueue();
}

void Floor::printPidDown()
{
	PriorityQueue<Pickable*> temp;
	Pickable* p;
	while (PidDown.peekFront(p)) {
		PidDown.dequeue(p);
		cout << p->getID() << ", ";
		temp.enqueue(p);
	}
	while (temp.peekFront(p)) {
		temp.dequeue(p);
		PidDown.enqueue(p);
	}
}

void Floor::printVidUp()
{
	VidUP.PrintList();
}

void Floor::printVidDown()
{
	VidDown.PrintList();
}

void Floor::printCidUp()
{
	CidUP.PrintQueue();
}

void Floor::printCidDown()
{
	CidDown.PrintQueue();
}

Pickable* Floor::decpwaitUP() {
	pwait--;
	Pickable* p;
	/*patients.dequeue(p);
	if (p->gettrg() > p->getsrc())
	{
		PidUP.dequeue(p);
	}
	else
	{
		PidDown.dequeue(p);
	}*/
	PidUP.dequeue(p);
	
	return p;

}
Pickable* Floor::decpwaitDown()
{
	Pickable* p;
	pwait--;
	PidDown.dequeue(p); //Add to completed list???

	return p;
}

Pickable* Floor::decvwaitUP() {
	vwait--;
	Pickable* p;
	VidUP.GetfirstNode(p);
	VidUP.DeleteFirst();
	/*Pickable* v;*/
	/*visitors.GetfirstNode(v);
	if (v->gettrg() > v->getsrc())
	{
		VidUP.DeleteNode(v);
	}
	else
	{
		VidDown.DeleteNode(v);
	}
	visitors.DeleteFirst();*/
	return p;
}
Pickable* Floor::decvwaitDown()
{
	Pickable* p;
	vwait--;
	VidDown.GetfirstNode(p);
	VidDown.DeleteFirst();
	return p;
}

Pickable* Floor::deccwaitUP() {
	cwait--;
	Pickable* p;
	CidUP.dequeue(p);


	/*cargo.dequeue(p);
	if (p->gettrg() > p->getsrc())
	{
		CidUP.DeleteNode(p->getID());
	}
	else
	{
		CidDown.DeleteNode(p->getID());
	}*/
	return p; ///////////////////////////////////////////////////////////////
}

Pickable* Floor::deccwaitDown()
{
	cwait--;
	Pickable* p;
	CidDown.dequeue(p);
	return p;
}




bool Floor::checkpWait()
{
	if (pwait != 0) return true;
	else return false;
}

bool Floor::checkcWait()
{
	if (cwait != 0) return true;
	else return false;
}

bool Floor::checkvWait()
{
	if (vwait != 0) return true;
	else return false;
}

bool Floor::ispidUpEmpty()
{
	if (PidUP.isEmpty()) return true;
	else return false;
}

bool Floor::ispidDownEmpty()
{
	if (PidDown.isEmpty()) return true;
	else return false;
}

bool Floor::isVidUPEmpty()
{
	if (VidUP.IsEmpty()) return true;
	else return false;
}

bool Floor::isVidDownEmpty()
{
	if (VidDown.IsEmpty()) return true;
	else return false;
}

bool Floor::isCidUPEmpty()
{
	if (CidUP.IsEmpty()) return true;
	else return false;
}

bool Floor::isCidDownEmpty(){
	if (CidDown.IsEmpty()) return true;
	else return false;
}

int Floor::getpwait() { return pwait; }
int Floor::getvwait() { return vwait; }
int Floor::getcwait() { return cwait; }
int Floor::getf() { return f; }

bool Floor::AutoStairsUp(int t, int autos, Pickable* &pick)
{
	return VidUP.checkAutoS(t, autos, pick);
}

bool Floor::AutoStairsDown(int t, int autos, Pickable*& pick)
{
	return VidDown.checkAutoS(t, autos, pick);
}

//search for visitor in the floor and returns true if found and deleted
bool Floor::delVisByID(int id, Pickable* &pick)
{
	//Pickable* v = visitors.GetPickableFromID(id);	
	pick = VidUP.GetPickableFromID(id);
	if (pick != nullptr)
	{
		if (pick->getStatus() == WAITING)
		{
			VidUP.DeleteNode(pick);
			vwait--;
			return true;
		}
		else return false;
	}
	pick = VidDown.GetPickableFromID(id);
	if (pick != nullptr)
	{
		if (pick->getStatus() == WAITING)
		{
			VidDown.DeleteNode(pick);
			vwait--;
			return true;
		}
		else return false;
	}
	
	if (pick == NULL)
	{
		return false;
	}

}


	
	//visitors.DeleteNode(visitors.GetPickableFromID(id))

Pickable* Floor::decpatients()
{
	Pickable* p;
	Pickable* r;
	PidUP.peekFront(p);
	PidDown.peekFront(r);
	if(!PidUP.peekFront(p))
	{
		r = decpwaitDown();
		return r;
	}
	if(!PidDown.peekFront(r))
	{
		p = decpwaitUP();
		return p;
	}
	if(p->getEmr() >= r->getEmr())
	{
		p = decpwaitUP();
		return p;
	}
	if(p->getEmr() < r->getEmr()){
		r = decpwaitDown();
		return r;
	}
}

Pickable* Floor::decvisitors()
{
	Pickable* p;
	Pickable* r;
	VidUP.GetfirstNode(p);
	VidDown.GetfirstNode(r);

	if(!VidUP.GetfirstNode(p))
	{
		r = decvwaitDown();
		return r;
	}
	if(!VidDown.GetfirstNode(r))
	{
		p = decvwaitUP();
		return p;
	}
	if(p->getTime() >= r->getTime())
	{
		p = decvwaitUP();
		return p;
	}
	if(p->getTime() < r->getTime()){
		r = decvwaitDown();
		return r;
	}

} 
Pickable* Floor::deccargo()
{
	Pickable* p;
	Pickable* r;
	CidUP.peek(p);
	CidDown.peek(r);
	if(!CidUP.peek(p))
	{
		r = deccwaitDown();
		return r;
	}
	if(!CidDown.peek(r))
	{
		p = deccwaitUP();
		return p;
	}
	if(p->getTime() >= r->getTime())
	{
		p = deccwaitUP();
		return p;
	}
	if(p->getTime() < r->getTime() ){
		r = deccwaitDown();
		return r;
	}

}
//Pickable* Floor :: getPickable(int id)
//{
//	return visitors.GetPickableFromID(id); //returns visitor with The given ID from Floor
//
//}
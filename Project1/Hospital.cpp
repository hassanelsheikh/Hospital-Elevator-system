#include "Hospital.h"
#include"Elevator.h"
#include"LinkedList.h"
#include"ListBag.h"
#include"UI.h"
#include"Events.h"
#include "Pickable.h"
#include "Arrival.h"
#include "Leave.h"
#include "Stairs.h"
#include"Floor.h"
#include<cstdlib>
#include"Node.h"
#include<dos.h>
#include<iostream>
#include <Windows.h>

using namespace std;
Hospital::Hospital() {
	timestep = 0;
	Tcomp = 0;
	Twait = 0;
	maxET = 0;
	Tleft = 0;
	stair = 0;
	inser = 0;
	Emove = 0;
}
void Hospital :: simulate() {
	UI* p = new UI;
	p->men1();
}
void Hospital :: createfloor(int& f) {
	for (int i = 0; i < f; i++) {
		Floor* f = new Floor(i);
		floors_List.InsertEnd(f);
	}
}



void Hospital :: getinfo(int& floor, int& VES, int& PES, int& CES, int& VEC, int& PEC, int& CEC, int& S, int& AutoS, int& E) {
	cfile >> floor;
	setNumOfFloors(floor);
	createfloor(floor);
	cfile >> VES >> PES >> CES;
	cfile >> VEC >> CEC >> PEC;
	cfile >> S >> AutoS;
	cfile >> E;
	Pick_Type picktype;
	char event;
	char type;
	int ET;
	int ID;
	int SRC;
	int TRG;
	int EMGLVL;
	for (int i = 0; i < E; i++) {
		cfile >> event;
		switch (event) {
		case 'A':
			cfile >> type >> ET >> ID >> SRC >> TRG;
			if (ET > maxET) {
				maxET = ET;
			}
			if (type == 'P') {
				picktype = TYPE_PTNT;
				cfile >> EMGLVL;
				Events* p = new Arrival(ID, ET, SRC, TRG, picktype, EMGLVL,event);
				events.enqueue(p);
			}
			else if (type == 'C') {
				picktype = TYPE_CRGO;
				Events* p = new Arrival(ID, ET, SRC, TRG, picktype,event);
				events.enqueue(p);
			}
			else if (type == 'V') {
				picktype = TYPE_VIS;
				Events* p = new Arrival(ID, ET, SRC, TRG, picktype, event);
				events.enqueue(p);
			}
			break;
		case 'L':
		{
			cfile >> ET >> ID;
			if (ET > maxET) {
				maxET = ET;
			}
			Events* p = new Leave(ET, ID, event);
			events.enqueue(p);
			break;
		}
		case 'S':
			cfile >> ET >> ID;
			if (ET > maxET) {
				maxET = ET;
			}
			Events* p = new Stairs(ET, ID, event);
			events.enqueue(p);
			break;
		}
	}
	cfile.close();
}
void Hospital::InteractiveMode(UI* p) {
	int numfloor=0;
	int VES = 0;
	int PES = 0; 
	int CES = 0; //elevators speed
	int VEC = 0;
	int PEC = 0;
	int CEC = 0; //elevator capacity
	int S = 0;
	int AutoS = 0;
	int E = 0;
	if (p->getfile(cfile)) {
		getinfo(numfloor, VES, PES, CES, VEC, PEC, CEC, S, AutoS, E);
	}
	pElev.setCapacity(PEC);
	//pElev.setEstate(AVAIL);
	pElev.setSpeed(PES);
	pElev.setType(EPTNT);
	vElev.setCapacity(VEC);
	//vElev.setEstate(AVAIL);
	vElev.setSpeed(VES);
	vElev.setType(EVIS);
	cElev.setCapacity(CEC);
	//cElev.setEstate(AVAIL);
	cElev.setSpeed(CES);
	cElev.setType(ECRGO);



	while (Twait != 0 || stair != 0 || inser != 0 || !events.IsEmpty())
	 {
		 executeEvents();
		 AddPicktoElev(numfloor);
		 p->men2(this,numfloor);
		 timestep++;
		 if (timestep >= S)
		 {
			 if (!stairsL.IsEmpty())
			 {
				 Pickable* p;
				 while (stairsL.checkstairs(timestep, S, p))
				 {
					 completed.InsertEnd(p);
					 stairsL.DeleteNode(p);
					 inser--;
					 stair--;
					 Tcomp++;
				 }
			 }
		 }

		 if (pElev.getEstate() == IDLE)
		 {
			 pElev.inctIdle();
			 if (pElev.gettIdle() == 3)
			 {
				 pElev.setEstate(AVAIL);
				 pElev.settIdle(0);
			 }
		 }

		 if (vElev.getEstate() == IDLE)
		 {
			 vElev.inctIdle();
			 if (vElev.gettIdle() == 3)
			 {
				 vElev.setEstate(AVAIL);
				 vElev.settIdle(0);
			 }
		 }

		 if (cElev.getEstate() == IDLE)
		 {
			 cElev.inctIdle();
			 if (cElev.gettIdle() == 3)
			 {
				 cElev.setEstate(AVAIL);
				 cElev.settIdle(0);
			 }
		 }
		  
		 if(timestep >= AutoS)
		 {
			 for(int i = 0; i < NumOfFloor ; i++)
			 {
				 Floor* f = floors_List.getFloorbySRC(i);
				 if (f->checkvWait())
				 {
					 Pickable* p;
					 while (f->AutoStairsUp(timestep, AutoS, p)) 
					 {
						 takestairsByVis(p->getID());
					 }
					 while (f->AutoStairsDown(timestep, AutoS, p))
					 {
						 takestairsByVis(p->getID());
					 }

				 }
			 }
			 /*if (!visitors.IsEmpty()) {
				 Pickable* p;
				 while (visitors.checkAutoS(timestep, AutoS, p)) {
					 takestairsByVis(p->getID());
				 }
			 }*/
		 }
			 
	 }
	 outputfile();
}
void Hospital::SilentMode(UI* p) 
{
	int numfloor = 0;
	int VES = 0;
	int PES = 0;
	int CES = 0; //elevators speed
	int VEC = 0;
	int PEC = 0;
	int CEC = 0; //elevator capacity
	int S = 0;
	int AutoS = 0;
	int E = 0;
	if (p->getfile(cfile)) {
		getinfo(numfloor, VES, PES, CES, VEC, PEC, CEC, S, AutoS, E);
	}
	pElev.setCapacity(PEC);
	pElev.setEstate(AVAIL);
	pElev.setSpeed(PES);
	pElev.setType(EPTNT);
	vElev.setCapacity(VEC);
	vElev.setEstate(AVAIL);
	vElev.setSpeed(VES);
	vElev.setType(EVIS);
	cElev.setCapacity(CEC);
	cElev.setEstate(AVAIL);
	cElev.setSpeed(CES);
	cElev.setType(ECRGO);
	for (int i = 0; i <= maxET; i++)
	{
		executeEvents();
		timestep++;

		if (timestep >= S)
		{
			if (!stairsL.IsEmpty())
			{
				Pickable* p;
				while (stairsL.checkstairs(timestep, S, p))
				{
					completed.InsertEnd(p);
					stairsL.DeleteNode(p);
					inser--;
					stair--;
					Tcomp++;
				}
			}
		}
		if (timestep >= AutoS)
		{
			for (int i = 0; i < NumOfFloor; i++)
			{
				Floor* f = floors_List.getFloorbySRC(i);
				if (f->checkvWait())
				{
					Pickable* p;
					while (f->AutoStairsUp(timestep, AutoS, p))
					{
						takestairsByVis(p->getID());
					}
					while (f->AutoStairsDown(timestep, AutoS, p))
					{
						takestairsByVis(p->getID());
					}

				}
			}
			/*if (!visitors.IsEmpty()) {
				Pickable* p;
				while (visitors.checkAutoS(timestep, AutoS, p)) {
					takestairsByVis(p->getID());
				}
			}*/
		}
		if (i == maxET) {
			p->men2silent(this);
		}
	}

}
void Hospital::StepByStepMode(UI* p) 
{
	int numfloor = 0;
	int VES = 0;
	int PES = 0;
	int CES = 0; //elevators speed
	int VEC = 0;
	int PEC = 0;
	int CEC = 0; //elevator capacity
	int S = 0;
	int AutoS = 0;
	int E = 0;
	if (p->getfile(cfile)) {
		getinfo(numfloor, VES, PES, CES, VEC, PEC, CEC, S, AutoS, E);
	}
	pElev.setCapacity(PEC);
	pElev.setEstate(AVAIL);
	pElev.setSpeed(PES);
	pElev.setType(EPTNT);
	vElev.setCapacity(VEC);
	vElev.setEstate(AVAIL);
	vElev.setSpeed(VES);
	vElev.setType(EVIS);
	cElev.setCapacity(CEC);
	cElev.setEstate(AVAIL);
	cElev.setSpeed(CES);
	cElev.setType(ECRGO);
	for (int i = 0; i <= maxET; i++)
	{
		executeEvents();
		Sleep(1000);
		p->men2stepbystep(this, numfloor);
		timestep++;

		if (timestep >= S)
		{
			if (!stairsL.IsEmpty())
			{
				Pickable* p;
				while (stairsL.checkstairs(timestep, S, p))
				{
					completed.InsertEnd(p);
					stairsL.DeleteNode(p);
					inser--;
					stair--;
					Tcomp++;
				}
			}
		}
		if (timestep >= AutoS)
		{
			for (int i = 0; i < NumOfFloor; i++)
			{
				Floor* f = floors_List.getFloorbySRC(i);
				if (f->checkvWait())
				{
					Pickable* p;
					while (f->AutoStairsUp(timestep, AutoS, p))
					{
						takestairsByVis(p->getID());
					}
					while (f->AutoStairsDown(timestep, AutoS, p))
					{
						takestairsByVis(p->getID());
					}

				}
			}
			/*if (!visitors.IsEmpty()) {
				Pickable* p;
				while (visitors.checkAutoS(timestep, AutoS, p)) {
					takestairsByVis(p->getID());
				}
			}*/
		}
		if (i == maxET) {
			outputfile();
		}
	}
}


void Hospital::settimestep(int t)
{
	timestep = t;
}

void Hospital::setwait(int wait)
{
	Twait = wait;
}

void Hospital::setdel(int d)
{
	Tcomp = d;
}

int Hospital::gettimestep()
{
	return timestep;
}

int Hospital::getTleft()
{
	return Tleft;
}

int Hospital::getInService()
{
	return inser;
}

int Hospital::getstair()
{
	return stair;
}

int Hospital::getNumOfFloors()
{
	return NumOfFloor;
}

int Hospital::PrintWait_P(int floor)
{
	Floor* f = floors_List.getFloorbySRC(floor);
	return f->getpwait();
}

int Hospital::PrintWait_V(int floor)
{
	Floor* f = floors_List.getFloorbySRC(floor);
	return f->getvwait();
}

int Hospital::PrintWait_C(int floor)
{
	Floor* f = floors_List.getFloorbySRC(floor);
	return f->getcwait();
}

int Hospital::getwait()
{
	return Twait;
}

int Hospital::getcomp()
{
	return Tcomp;
}

int Hospital::getdel()
{
	return Tcomp;
}


void Hospital::setNumOfFloors(int f)
{
	NumOfFloor = f;
}

void Hospital::PrintPIdUp(int floor)
{
	Floor* f = floors_List.getFloorbySRC(floor);
	f->printPidUp();
}

void Hospital::PrintPIdDown(int f)
{
	Floor* floor = floors_List.getFloorbySRC(f);
	floor->printPidDown();
}

void Hospital::PrintVisUp(int f)
{
	Floor* floor = floors_List.getFloorbySRC(f);
	floor->printVidUp();
}

void Hospital::PrintVisDown(int f)
{
	Floor* floor = floors_List.getFloorbySRC(f);
	floor->printVidDown();
}

void Hospital::PrintCIdUp(int f)
{
	Floor* floor = floors_List.getFloorbySRC(f);
	floor->printCidUp();
}

void Hospital::PrintCIdDown(int f)
{
	Floor* floor = floors_List.getFloorbySRC(f);
	floor->printCidDown();
}

void Hospital::printelevPstat()
{
	if (pElev.getEstate() == AVAIL)
	{
		cout << "Avail";
	}
	else if (pElev.getEstate() == IDLE) 
	{
		cout << "IDLE";
	}
	else if (pElev.getEstate() == MOVUP || pElev.getEstate() == MOVDN)
	{
		cout << "MOVING";
	}
	else if (pElev.getEstate() == OUTOFSER)
	{
		cout << "OUT";
	}
	else if(pElev.getEstate()== UNLOAD) 
	{
		cout << "UNLOAD";
	}
}

void Hospital::printelevVstat()
{
	if (vElev.getEstate() == AVAIL) {
		cout << "Avail";
	}
	else if (vElev.getEstate() == IDLE) {
		cout << "IDLE";
	}
	else if (vElev.getEstate() == MOVUP || vElev.getEstate() == MOVDN) {
		cout << "MOVING";
	}
	else if (vElev.getEstate() == OUTOFSER) {
		cout << "OUT";
	}
	else if (vElev.getEstate() == UNLOAD) {
		cout << "UNLOAD";
	}
}

void Hospital::printelevCstat()
{
	if (cElev.getEstate() == AVAIL) {
		cout << "Avail";
	}
	else if (cElev.getEstate() == IDLE) {
		cout << "IDLE";
	}
	else if (cElev.getEstate() == MOVUP || cElev.getEstate() == MOVDN) {
		cout << "MOVING";
	}
	else if (cElev.getEstate() == OUTOFSER) {
		cout << "OUT";
	}
	else if (cElev.getEstate() == UNLOAD) {
		cout << "UNLOAD";
	}
}
void Hospital::setEcap(Elevator* elev, int c)
{
	elev->setCapacity(c);
}

void Hospital::AddtoQueue(Pickable* pick)
{
	Pick_Type type = pick->getType();
	Floor* f = floors_List.getFloorbySRC(pick->getsrc());
	switch (type)
	{
	case TYPE_PTNT:
		
		f->incpwait(pick);
		//patients.enqueue(pick);
		break;

	case TYPE_VIS:

		f->incvwait(pick);
		//visitors.InsertEnd(pick);
		break;

	case TYPE_CRGO:

		f->inccwait(pick);
		//cargo.enqueue(pick);
		break;

	default:

		return;

	}

}


//deletes visitor if he decides to leave at any time
bool Hospital::DeletePass(int ID)
{
	Pickable* temp;
	bool x;
	for (int i = 0; i < getNumOfFloors(); i++)
	{
		Floor* f = floors_List.getFloorbySRC(i);
		x = f->delVisByID(ID, temp);
		if (x)
		{
			Twait--;
			Tleft++;
			return true;
		}
	}

	return false;
	


	//Pickable* pHos = visitors.GetPickableFromID(ID);
	//Floor* f = floors_List.getFloorbySRC(pHos->getsrc());

	//f->delVisByID(ID, pHos->getsrc(),pHos->gettrg());
	//if (pHos)
	//{
	//	PICK_STATUS status = pHos->getStatus();

	//	if (status == WAITING) {
	//		Twait--;
	//		Tleft++;
	//	}
	//	return visitors.DeleteNode(pHos);
	//}
}

void Hospital::AddPicktoElev(int numf)
{

for (int i = 0; i < numf; i++)
{
	Pickable* p;
	Floor* f = floors_List.getFloorbySRC(i);
	int mininreq = 0;
	if (pElev.geteFloor() == f->getf() && (f->checkpWait() || (f->checkvWait() && (vElev.checkFull() || vElev.geteFloor() != f->getf()))) && !pElev.checkFull() && pElev.getEstate() == AVAIL)
	{
		while (!pElev.checkFull() && f->checkpWait()) {
			if (pElev.geteTrg() == -1) {
				p = f->decpatients();
				pElev.AddToElevList(p);
				pElev.seteTrg(p->gettrg());
				Twait--;
				inser++;
			}
			else if (pElev.peekload()->gettrg() > f->getf()) 
			{
				if (f->ispidUpEmpty()) break;
				p = f->decpwaitUP();
				pElev.AddToElevList(p);
				Twait--;
				inser++;
			}
			else if (pElev.peekload()->gettrg() < f->getf())
			{
				if (f->ispidDownEmpty()) break;
				p = f->decpwaitDown();
				pElev.AddToElevList(p);
				Twait--;
				inser++;
			}
		}
		while (!pElev.checkFull() && (vElev.checkFull() || vElev.geteFloor() != f->getf()) && f->checkvWait()) {
			if (pElev.geteTrg() == -1) {
				p = f->decvisitors();
				pElev.AddToElevList(p);
				pElev.seteTrg(p->gettrg());
				
				Twait--;
				inser++;
			}
			if (pElev.peekload()->gettrg() > f->getf()) {
				if (f->isVidUPEmpty()) break;
				p = f->decvwaitUP();
				pElev.AddToElevList(p);
				Twait--;
				inser++;
			}
			if (pElev.peekload()->gettrg() < f->getf()) {
				if (f->isVidDownEmpty()) break;
				p = f->decvwaitDown();
				pElev.AddToElevList(p);
				Twait--;
				inser++;
			}
		}
	}
	if (vElev.geteFloor() == f->getf() && (f->checkvWait() || (f->checkpWait() && (pElev.checkFull() || pElev.geteFloor() != f->getf()))) && !vElev.checkFull() && vElev.getEstate() == AVAIL)
	{
		while (!vElev.checkFull() && (pElev.checkFull() || pElev.geteFloor() != f->getf()) && f->checkpWait()) {
			if (vElev.geteTrg() == -1) {
				p = f->decpatients();
				vElev.AddToElevList(p);
				vElev.seteTrg(p->gettrg());
				Twait--;
				inser++;
			}
			if (vElev.peekload()->gettrg() > f->getf()) {
				if (f->ispidUpEmpty()) break;
				p = f->decpwaitUP();
				vElev.AddToElevList(p);
				Twait--;
				inser++;
			}
			if (vElev.peekload()->gettrg() < f->getf()) {
				if (f->ispidDownEmpty()) break;
				p = f->decpwaitDown();
				vElev.AddToElevList(p);
				Twait--;
				inser++;
			}
		}
		while (!vElev.checkFull() && f->checkvWait()) {
			if (vElev.geteTrg() == -1) {
				p = f->decvisitors();
				vElev.AddToElevList(p);
				vElev.seteTrg(p->gettrg());
				Twait--;
				inser++;
			}
			if (vElev.peekload()->gettrg() > f->getf()) {
				if (f->isVidUPEmpty()) break;
				p = f->decvwaitUP();
				vElev.AddToElevList(p);
				Twait--;
				inser++;
			}
			if (vElev.peekload()->gettrg() < f->getf()) {
				if (f->isVidDownEmpty()) break;
				p = f->decvwaitDown();
				vElev.AddToElevList(p);
				Twait--;
				inser++;
			}
		}
	}
	if (cElev.geteFloor() == f->getf() && (f->checkcWait() || (f->checkvWait() && (vElev.checkFull() || vElev.geteFloor() != f->getf())) || (f->checkpWait() && (pElev.checkFull() || pElev.geteFloor() != f->getf()))) && !cElev.checkFull() && cElev.getEstate() == AVAIL)
	{
		while (!cElev.checkFull() && (pElev.checkFull() || pElev.geteFloor() != f->getf()) && f->checkpWait()) {
			if (cElev.geteTrg() == -1) {
				p = f->decpatients();
				cElev.AddToElevList(p);
				cElev.seteTrg(p->gettrg());
				Twait--;
				inser++;
			}
			if(cElev.peekload()->getType() == TYPE_CRGO)
			{
				break;
			}
			if (cElev.peekload()->gettrg() > f->getf()) {
				if (f->ispidUpEmpty()) break;
				p = f->decpwaitUP();
				cElev.AddToElevList(p);
				Twait--;
				inser++;
			}
			if (cElev.peekload()->gettrg() < f->getf()) {
				if (f->ispidDownEmpty()) break;
				p = f->decpwaitDown();
				cElev.AddToElevList(p);
				Twait--;
				inser++;
			}
		}
		while (!cElev.checkFull() && f->checkcWait()) {
			if (cElev.geteTrg() == -1) {
				p = f->deccargo();
				cElev.AddToElevList(p);
				cElev.seteTrg(p->gettrg());
				Twait--;
				inser++;
			}
			if (cElev.peekload()->gettrg() > f->getf()) {
				if (f->isCidUPEmpty()) break;
				p = f->deccwaitUP();
				cElev.AddToElevList(p);
				Twait--;
				inser++;
			}
			if (cElev.peekload()->gettrg() < f->getf()) {
				if (f->isCidDownEmpty()) break;
				p = f->deccwaitDown();
				cElev.AddToElevList(p);
				Twait--;
				inser++;
			}
		}
	}
 }

}

bool Hospital::checkIfValid(Elev_TYPE t, Pickable* p)
{
	if (t != ECRGO && p->getType() == TYPE_CRGO)
	{
		return false;
	}
	if (p->getType() == TYPE_VIS && ((t == ECRGO) || (t==EPTNT && (vElev.geteFloor()==p->getsrc()) && !vElev.checkFull())))
	{
		return false;
	}
	if ((p->getType() == TYPE_PTNT) && t == ECRGO && cElev.peekload()->getType() == TYPE_CRGO)
	{
		return false;
	}
	return true;

}

void Hospital::takestairsByVis(int ID) 
{
	Pickable* pHos;
	
	bool x;
	for (int i = 0; i < NumOfFloor; i++)
	{
		Floor* f = floors_List.getFloorbySRC(i);
		x = f->delVisByID(ID, pHos);
		if (x)
		{
			pHos->setstairtime(timestep);
			Twait--;
			inser++;
			stair++;
			stairsL.InsertEnd(pHos);
		}
	}

}

void Hospital::executeEvents()
{
	Events* p;
	while (events.peek(p)) //while events queue is not empty
	{
		if (p->getET() == timestep) {
			p->Execute(this);
			events.dequeue(p); //removes event 
		}
		else break;
	}
 }

bool Hospital::outputfile() {
	outfile.open("output");
	if (outfile.is_open()) {
		outfile << "total waiting pass/cargos: " << Twait << endl;
		outfile << "Total Completed: " << Tcomp << endl;
		return true;
	}
	else { return false; }
	outfile.close();
}

void Hospital::checkForrequests(int nfloor)
{
	int maxPreq = 0;
	int maxVreq = 0;
	int maxCreq = 0;
	int minPreq = NumOfFloor - 1;
	int minVreq = NumOfFloor - 1;
	int minCreq = NumOfFloor - 1;
	//if (pElev.geteFloor() == 0 || pElev.getEstate() == MOVUP)
	//{
	//	for (int i = 0; i < nfloor; i++)
	//	{
	//		if (maxf < floors_List.getFloorbySRC(i)->getf() && floors_List.getFloorbySRC(i)->checkpWait())
	//		{
	//			maxf = floors_List.getFloorbySRC(i)->getf();
	//		}
	//	}
	//	pElev.setMaxOut(maxf);
	//}

	//if ( pElev.getEstate() == MOVDN)
	//{
	//	for (int i = 0; i < nfloor; i++)
	//	{
	//		if (minf > floors_List.getFloorbySRC(i)->getf() && floors_List.getFloorbySRC(i)->checkpWait())
	//		{
	//			minf = floors_List.getFloorbySRC(i)->getf();
	//		}
	//	}
	//	pElev.seteTrg(minf); /////////////////////////////////////////////////////////////////
	//}

	//if (pElev.getEstate() == AVAIL)
	//{
	//	for (int i = 0; i < nfloor; i++)
	//	{
	//		if (maxf > floors_List.getFloorbySRC(i)->getf() && floors_List.getFloorbySRC(i)->checkpWait())
	//		{
	//			maxf = floors_List.getFloorbySRC(i)->getf();
	//		}
	//	}

	//	for (int i = 0; i < nfloor; i++)
	//	{
	//		if (minf > floors_List.getFloorbySRC(i)->getf() && floors_List.getFloorbySRC(i)->checkpWait())
	//		{
	//			minf = floors_List.getFloorbySRC(i)->getf();
	//		}
	//	}
	//	
	//	//check which floor is closer and move to the closer one(Up or down), if equal move up
	//	if (abs(pElev.geteFloor() - maxf) <= abs(pElev.geteFloor() - minf))
	//	{
	//		pElev.seteTrg(maxf);
	//	}
	//	else
	//	{
	//		pElev.seteTrg(minf);
	//	}
	//}
	for (int i = 0; i < nfloor; i++)
	{
		if (maxPreq < floors_List.getFloorbySRC(i)->getf() && !floors_List.getFloorbySRC(i)->checkpWait())
		{
			maxPreq = floors_List.getFloorbySRC(i)->getf();
		}
		if (maxVreq < floors_List.getFloorbySRC(i)->getf() && !floors_List.getFloorbySRC(i)->checkvWait())
		{
			maxVreq = floors_List.getFloorbySRC(i)->getf();
		}
		if (maxCreq < floors_List.getFloorbySRC(i)->getf() && !floors_List.getFloorbySRC(i)->checkcWait())
		{
			maxCreq = floors_List.getFloorbySRC(i)->getf();
		}
		if (minPreq > floors_List.getFloorbySRC(i)->getf() && !floors_List.getFloorbySRC(i)->checkpWait())
		{
			minPreq = floors_List.getFloorbySRC(i)->getf();
		}
		if (minVreq > floors_List.getFloorbySRC(i)->getf() && !floors_List.getFloorbySRC(i)->checkvWait())
		{
			minVreq = floors_List.getFloorbySRC(i)->getf();
		}
		if (minCreq > floors_List.getFloorbySRC(i)->getf() && !floors_List.getFloorbySRC(i)->checkcWait())
		{
			minCreq = floors_List.getFloorbySRC(i)->getf();
		}
	}
	if (pElev.getEstate() == MOVUP && pElev.geteFloor() < maxPreq) {
		pElev.setMaxOut(maxPreq);
	}
	if (vElev.getEstate() == MOVUP && vElev.geteFloor() < maxVreq) {
		vElev.setMaxOut(maxVreq);
	}
	if (cElev.getEstate() == MOVUP && cElev.geteFloor() < maxCreq) {
		cElev.setMaxOut(maxCreq);
	}
	if (pElev.getEstate() == MOVDN && pElev.geteFloor() > minPreq) {
		pElev.setMinOut(minPreq);
	}
	if (vElev.getEstate() == MOVDN && vElev.geteFloor() > minVreq) {
		vElev.setMinOut(minVreq);
	}
	if (cElev.getEstate() == MOVDN && cElev.geteFloor() > minCreq) {
		cElev.setMinOut(minCreq);
	}
	if (pElev.getEstate() == AVAIL) {
		if (abs(pElev.geteFloor() - maxPreq) <= abs(pElev.geteFloor() - minPreq) && pElev.geteFloor() < maxPreq)
		{
			pElev.setMaxOut(maxPreq);
		}
		else
		{
			pElev.setMinOut(minPreq);
		}
	}
	if (vElev.getEstate() == AVAIL) {
		if (abs(vElev.geteFloor() - maxVreq) <= abs(vElev.geteFloor() - minVreq) && vElev.geteFloor() < maxVreq)
		{
			vElev.setMaxOut(maxVreq);
		}
		else
		{
			vElev.setMinOut(minVreq);
		}
	}
	if (cElev.getEstate() == AVAIL) {
		if (abs(cElev.geteFloor() - maxCreq) <= abs(cElev.geteFloor() - minCreq) && cElev.geteFloor() < maxCreq)
		{
			cElev.setMaxOut(maxCreq);
		}
		else
		{
			cElev.setMinOut(minCreq);
		}
	}

}

void Hospital::printInElev(Elev_TYPE t)
{
	switch (t)
	{
	case EPTNT:
		pElev.printElevList();
		break;
	case EVIS:
		vElev.printElevList();
		break;
	case ECRGO:
		cElev.printElevList();
		break;
	}
}



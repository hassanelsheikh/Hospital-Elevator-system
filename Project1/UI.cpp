#include "UI.h"
#include"Hospital.h"
#include"Floor.h"
#include"defs.h"
#include"Elevator.h"
#include<fstream>


bool UI :: getfile(ifstream& file) {
	cout << "Please Type The name of the file:";
	string f;
	cin >> f;
    filename= f +".txt";
	file.open(filename, ios::in);
	if(file.is_open()){
		cout << "File loaded:)"<< endl;
		return true;
	}
	else {
		cout << "couldn't load file:(";
		return false;
	}
}
void UI::men2stepbystep(Hospital* p, int& floor)
{
		cout << "Current timestamp:" << p->gettimestep() << endl;
		for (int i = floor - 1; i >= 0; i--)
		{
			if (i != 0)
			{
				cout << p->PrintWait_P(i) << " Waiting Patients: UP[";
				p->PrintPIdUp(i);
				cout << "] Down[";
				p->PrintPIdDown(i);
				cout << "]" << endl;
				cout << p->PrintWait_C(i) << " Waiting cargos: UP[";
				p->PrintCIdUp(i);
				cout << "] Down[";
				p->PrintCIdDown(i);
				cout << "]" << endl;
				cout << p->PrintWait_V(i) << " Waiting Visitors: UP[";
				p->PrintVisUp(i);
				cout << "] Down[";
				p->PrintVisDown(i);
				cout << "]" << endl;
				cout << "Elevators: None" << endl;
				cout << "--------------------------- Floor" << i << "--------------------------" << endl;
			}
			else
			{
				cout << p->PrintWait_P(i) << " Waiting Patients: UP[";
				p->PrintPIdUp(i);
				cout << "] Down[";
				p->PrintPIdDown(i);
				cout << "]" << endl;
				cout << p->PrintWait_C(i) << " Waiting cargos: UP[";
				p->PrintCIdUp(i);
				cout << "] Down[";
				p->PrintCIdDown(i);
				cout << "]" << endl;
				cout << p->PrintWait_V(i) << " Waiting Visitors: UP[";
				p->PrintVisUp(i);
				cout << "] Down[";
				p->PrintVisDown(i);
				cout << "]" << endl;
				cout << "Elevators: V[ Not Moving, ";
				p->printelevPstat();
				cout << "], ";
				cout << "C[ Not Moving, ";
				p->printelevCstat();
				cout << "], ";
				cout << "V[Not Moving, ";
				p->printelevVstat();
				cout << "]" << endl;
				cout << "--------------------------- Ground --------------------------" << endl;
				cout << p->getwait() << " total waiting pass/cargos ( " << p->getTleft() << " Visitors Left)" << endl;
				cout << p->getInService() << " total in service pass/cargo ( " << p->getstair() << " Visitors by stairs)" << endl;
				cout << p->getcomp() << " total completed pass/cargo" << endl;
			}
		}
}
void UI::men2silent(Hospital* p)
{
	if (p->outputfile()) {
		cout << "Simulation ended, output file created";
	}
}
void UI::men1() {
		Hospital* H = new Hospital;
		cout << "Hello Please chose a Mode.." << endl;
		cout << "1.Interactive Mode" << endl;
		cout << "2.Step by step Mode" << endl;
		cout << "3.Silent Mode" << endl;
		int M;
		cin >> M;
		if (M == 1) {
			cout << "Thanks For choosing Interactive Mode:)"<<endl;
			H->InteractiveMode(this);
		}
		else if (M == 2) {
			cout << "Thanks for choosing Step by Step Mode:)";
			H->StepByStepMode(this);
		}
		else if (M == 3) {
			cout << "Thanks for choosing Silent Mode:)";
			H->SilentMode(this);
		}
}
void UI :: men2(Hospital* p,int& floor) {
	char w;
	cout << "Press W to continue";
	cin >> w;
	if (w == 'w') {
		cout << "Current timestamp:" << p->gettimestep() << endl;
		for (int i = floor-1 ; i >= 0 ; i--)
		{
			if (p->gettimestep() == 13 && i==5) {
				int x = 0;
			}
			if (i != 0)
			{
				cout << p->PrintWait_P(i) << " Waiting Patients: UP[";
				p->PrintPIdUp(i);
				cout << "] Down[";
				p->PrintPIdDown(i);
				cout << "]" << endl;
				cout << p->PrintWait_C(i) << " Waiting cargos: UP[";
				p->PrintCIdUp(i);
				cout << "] Down[";
				p->PrintCIdDown(i);
				cout << "]" << endl;
				cout << p->PrintWait_V(i) << " Waiting Visitors: UP[";
				p->PrintVisUp(i);
				cout << "] Down[";
				p->PrintVisDown(i);
				cout << "]" << endl;
				cout << "Elevators: None"<<endl;
				cout << "--------------------------- Floor" << i << "--------------------------" << endl;
			}
			else
			{
				cout << p->PrintWait_P(i) << " Waiting Patients: UP[";
				p->PrintPIdUp(i);
				cout << "] Down[";
				p->PrintPIdDown(i);
				cout << "]" << endl;
				cout << p->PrintWait_C(i) << " Waiting cargos: UP[";
				p->PrintCIdUp(i);
				cout << "] Down[";
				p->PrintCIdDown(i);
				cout << "]" << endl;
				cout << p->PrintWait_V(i) << " Waiting Visitors: UP[";
				p->PrintVisUp(i);
				cout << "] Down[";
				p->PrintVisDown(i);
				cout << "]" << endl;
				cout << "Elevators: P[ Not Moving, ";
				p->printelevPstat();
				cout << ",";
				p->printInElev(EPTNT);
				cout << "], ";
				cout << "C[ Not Moving, ";
				p->printelevCstat();
				cout << ",";
				p->printInElev(ECRGO);
				cout << "], ";
				cout << "V[Not Moving, ";
				p->printelevVstat();
				cout << ",";
				p->printInElev(EVIS);
				cout<< "]" << endl;
				cout << "--------------------------- Ground --------------------------" << endl;
				cout << p->getwait() << " total waiting pass/cargos ( " << p->getTleft() <<" Visitors Left)"<< endl;
				cout << p->getInService() << " total in service pass/cargo ( " << p->getstair() << " Visitors by stairs)" << endl;
				cout << p->getcomp() << " total completed pass/cargo" << endl;
			}
		}
	}

}
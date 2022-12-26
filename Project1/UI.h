#pragma once
#include<iostream>
#include"Hospital.h"
#include<fstream>
#include<string>
using namespace std;

class Hospital;
class UI
{
private:
	ifstream file;
	string filename;
public:
	void men1();
	void men2(Hospital* p, int& floor);
	bool getfile(ifstream& file);
	void men2stepbystep(Hospital* p, int& floor);
	void men2silent(Hospital* p);
};


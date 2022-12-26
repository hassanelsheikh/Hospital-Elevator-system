#include<iostream>
#include"Hospital.h"
using namespace std;

int main() {
	Hospital* H = new Hospital;
	H->simulate();
	delete H;
	return 0;
}
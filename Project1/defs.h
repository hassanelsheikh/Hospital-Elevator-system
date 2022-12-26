#pragma once

enum Pick_Type //type of pickable
{
	TYPE_PTNT,	//patient
	TYPE_VIS,	//Visitor
	TYPE_CRGO	//Cargo

};

enum Elev_TYPE
{
	EPTNT,
	EVIS,
	ECRGO
};



enum PICK_STATUS    //cargo status
{
	WAITING,    //waiting to be deliverd
	INSRVC,    //loading 
	CMPLT,    // completed 
};

enum ELEV_STATUS
{
	IDLE,	//idle
	MOVUP,	//Moving
	MOVDN,
	UNLOAD,	//Unloading pass,cargos
	AVAIL,	//Available
	OUTOFSER	//out of service
};


enum PROG_MODE	//Mode of program interface
{
	MODE_INTR,  //interactive mode
	MODE_STEP,	//step-by-step mode
	MODE_SLNT,	//silent mode
	MODE_DEMO,	
	MODE_CNT	//number of possible modes
};
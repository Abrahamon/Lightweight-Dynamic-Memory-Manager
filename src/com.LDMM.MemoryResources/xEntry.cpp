/*
 * xEntry.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: fabian
 */

#include "xEntry.h"
#include <string>
#include <iostream>
xEntry::xEntry(int pID,int pSize, int pOffset, string pType) {
	_ID = pID;
	_Size = pSize;
	_Offset = pOffset;
	_Type = pType;
	_UseFlag = true;
	_RefCounter = 1;
}

xEntry::~xEntry() {}

//Métodos Getters
int xEntry::getID(){ return _ID; }
int xEntry::getSize(){ return _Size; }
int xEntry::getOffset(){ return _Offset; }
int xEntry::getReferenceCounter(){ return _RefCounter; }
bool xEntry::isBeingUsed(){ return _UseFlag; }
string xEntry::getType(){ return _Type; }

//Métodos Setters
void xEntry::setSize(int pSize){ _Size = pSize; }
void xEntry::setOffset(int pOffset){ _Offset = pOffset; }
void xEntry::setUseFlag(bool pFlag){ _UseFlag = pFlag; }
void xEntry::setType(string pType){ _Type = pType; }
void xEntry::IncreaseRef(){
	std::cout << "increase";
	_RefCounter++;
}
void xEntry::DecreaseRef(){
	if(_RefCounter <= 0){
		_RefCounter = 0;
	}
	else{
		_RefCounter--;
	}
}

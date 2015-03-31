/*
 * xTable.cpp
 *
 *  Created on: Mar 16, 2015
 *      Author: fabian
 */
#include <stdlib.h>
#include "xTable.h"
#include "xEntry.h"
#include "../com.LDMM.DataStructures/vLinkedList.h"
#include "../Constants.h"


xTable::xTable() {}
xTable::~xTable() {}

xTable* xTable::_xHashTable = 0;
vLinkedList<xEntry*>* xTable::_ObjectsList;

xTable* xTable::getInstance(){
	if(_xHashTable == 0){
		static xTable self;

		_xHashTable = &self;
		_ObjectsList = new vLinkedList<xEntry*>;
	}
	return _xHashTable;
}

xEntry* xTable::getObjectInfo(int pID){
	Node<xEntry*>* tmpEntry = _ObjectsList->getHead();
	for(int i = 0; i < pID; i++){
		tmpEntry = tmpEntry->getNext();
	}
	return tmpEntry->getData();
}

int xTable::getOffSetDelXEntry(int pID)
{
	for(Node<xEntry*>* tmpEntry = _ObjectsList->getHead(); tmpEntry != 0 ; tmpEntry = tmpEntry->getNext()){
		if(tmpEntry->getData()->getID() == pID)
		{
			return tmpEntry->getData()->getOffset();
		}
	}
	return -1;
}

int xTable::addEntry(int pSize,int pOffset,string pType){
	//int pID = _ObjectsList->getLength();
	int pID = _ObjectsList->getTail()->getData()->getID()+1;
	/*int* pointer = (int*)malloc(1 * sizeof(xEntry));
	xEntry temp = new xEntry(pID,pSize,pOffset,pType);
	xEntry temp = *pointer;*/

	xEntry* temp = new xEntry(pID,pSize,pOffset,pType);
	_ObjectsList->insertTail(temp);
	return pID;
}

vLinkedList<xEntry*>* xTable::getList()
{
	return this->_ObjectsList;
}

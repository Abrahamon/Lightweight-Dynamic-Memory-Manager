/*
 * xTable.h
 *
 *  Created on: Mar 16, 2015
 *      Author: fabian
 */

#ifndef SRC_XTABLE_H_
#define SRC_XTABLE_H_
#include "../com.LDMM.DataStructures/vLinkedList.h"
#include "xEntry.h"

class xTable {
private:
	static xTable* _xHashTable;
	static vLinkedList<xEntry*>* _ObjectsList;
	static int _CurrOffset;

public:
	xTable();
	~xTable();
	static xTable* getInstance();
	xEntry* getObjectInfo(int pID);
	int addEntry(int pSize,void* pOffset,string pType);
	vLinkedList<xEntry*>* getList();
};

#endif /* SRC_XTABLE_H_ */

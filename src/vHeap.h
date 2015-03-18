/*
 * xTable.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: Abraham
 */

#ifndef SRC_VHEAP_H_
#define SRC_VHEAP_H_

#include "xTable.h"

class vHeap{

private:
	int size;
	int overweight;
	xTable* tabla;

public:
	vHeap(int pSize, int pOverweight);
/*vRef*/void vMalloc(int pSize, std::string pType);
	void vFree(/*vRef*/);

};

#endif /* SRC_VHEAP_H */

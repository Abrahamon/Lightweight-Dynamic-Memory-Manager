/*
 * xTable.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: Abraham
 */

#ifndef SRC_VHEAP_H_
#define SRC_VHEAP_H_

#include "xTable.h"
#include <stdlib.h>

class vHeap{

private:
	int size;
	int overweight;
	xTable* tabla;
	void* memoriaFisica;

public:
	vHeap(int pSize, int pOverweight);
	~vHeap();
/*vRef*/void vMalloc(int pSize, std::string pType);
	void vFree(/*vRef*/);
	void vFreeAll();


};

#endif /* SRC_VHEAP_H */

/*
 * xTable.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: Abraham
 */

#ifndef SRC_VHEAP_H_
#define SRC_VHEAP_H_

#include "xTable.h"
#include "vRef.h"
#include <stdlib.h>
#include "garbageCollector.h"

class vHeap{

private:
	static vHeap* HEAP;

	int size;
	int overweight;
	xTable* tabla;
	void* memoriaFisica;
	void* ptrNextPosicion;
	garbageCollector* ColectorDeBasura;

public:
	vHeap(int pSize, int pOverweight);
	~vHeap();

	static vHeap* getInstancia();

	vRef* vMalloc(int pSize, std::string pType);
	void vFree(/*vRef*/);
	void vFreeAll();


	void dumpMemory();

};

#endif /* SRC_VHEAP_H */

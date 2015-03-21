/*
 * xTable.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: Abraham
 */

#ifndef SRC_VHEAP_H_
#define SRC_VHEAP_H_

#include "../com.LDMM.MemoryResources/xTable.h"
#include "../com.LDMM.MemoryResources/vRef.h"
#include <stdlib.h>

#include "../com.LDMM.MemoryManager/garbageCollector.h"

class vHeap{

private:
	static vHeap* HEAP;

	int size;
	int overweight;
	xTable* tabla;
	void* memoriaFisica;
	void* offsetVHeap;
	garbageCollector* ColectorDeBasura;
	bool zonaCritica;

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

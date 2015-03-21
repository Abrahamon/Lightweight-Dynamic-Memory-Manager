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
#include "../com.LDMM.MemoryManager/garbageCollector.h"
#include "../Constants.h"
#include <stdlib.h>
#include <unistd.h>

class vHeap{

private:
	static vHeap* HEAP;

	int tamanovHeap;
	xTable* tablaMetadatos;
	void* ptrInicioMemoria;
	void* ptrUltimaMemoriaLibre;
	garbageCollector* ColectorDeBasura;
	bool zonaCritica;//todos los metodos al final deben asignarle false

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

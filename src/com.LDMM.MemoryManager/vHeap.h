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
#include "../Constants.h"
#include "../com.LDMM.DataStructures/vLinkedList.h"
#include "../com.LDMM.DataStructures/vNode.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>


class vHeap{

private:

	static vHeap* HEAP;
	int tamanovHeap;
	xTable* tablaMetadatos;
	void* ptrInicioMemoria;

	bool zonaCritica;//todos los metodos al final deben asignarle false
	static bool vDEBUG;

	vHeap(int pSize, int pOverweight);
	~vHeap();
	void vFree(/*vRef*/);
	void vFreeAll();
	void dumpMemory();
	void garbageCollector();
	void desfragmentar();
	void control(); //hilo que controla fragmentacion, garbage colector y dump de memoria.

public:
	void* ptrUltimaMemoriaLibre;
	static vHeap* getInstancia();
	vRef * vMalloc(int pSize, std::string pType);
	void vFree(vRef* pRef);


};

#endif /* SRC_VHEAP_H */

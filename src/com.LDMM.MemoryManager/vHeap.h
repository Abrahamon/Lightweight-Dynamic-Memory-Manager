/*
 * xTable.cpp
 *
 *  Created on: Mar 17, 2015
 *      Author: Abraham
 */

#ifndef SRC_VHEAP_H_
#define SRC_VHEAP_H_

#include "../Constants.h"
#include "../com.LDMM.MemoryResources/xTable.h"
#include "../com.LDMM.vObjects/vInt.h"
#include "../com.LDMM.MemoryResources/vRef.h"
#include "../com.LDMM.DataAccess/XMLWriter.h"
#include "../com.LDMM.DataStructures/vLinkedList.h"
#include "../com.LDMM.DataStructures/vNode.h"

#include "../com.LDMM.DataAccess/Encoder.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <string>
#include <fstream>
#include <cstring>

class vHeap{

private:
	static vHeap* HEAP;
	int _overweight;
	int _tamanovHeap;
	int _contador;
	int _tamanoMemoriaPaginadaUsada;
	xTable* _tablaMetadatos;
	void* _ptrInicioMemoria;

	bool _estaEnZonaCritica;//todos los metodos al final deben asignarle false

	void vFreeAll();
	vHeap(int pSize, int pOverweight);
	~vHeap();
	void vFree(xEntry* pEntry);
	void garbageCollector();

	void control(); //hilo que controla fragmentacion, garbage colector y dump de memoriaa.


public:
	void dumpMemory();
	bool paginar(int pSize);
	void* _ptrUltimaMemoriaLibre;
	static vHeap* getInstancia();
	Encoder* _encoder;
	vRef* vMalloc(int pSize, std::string pType);
	void vFree(vRef* pRef);
	void desfragmentar();



};

#endif /* SRC_VHEAP_H */

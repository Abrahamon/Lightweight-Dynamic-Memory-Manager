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
#include "../com.LDMM.vObjects/vLong.h"
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
#include <pthread.h>
#include <time.h>

class vHeap{

private:
	static vHeap* HEAP;
	int _overweight;
	int _tamanovHeap;
	static int _contador;
	int _tamanoMemoriaPaginadaUsada;
	static xTable* _tablaMetadatos;


	static bool _estaEnZonaCritica;//todos los metodos al final deben asignarle false

	void vFreeAll();
	vHeap(int pSize, int pOverweight);
	~vHeap();
	static void vFree(xEntry* pEntry);
	static void garbageCollector();




public:
	static void* _ptrInicioMemoria;
	static void dumpMemory();
	bool paginar(int pSize);
	void* _ptrUltimaMemoriaLibre;
	static vHeap* getInstancia();
	Encoder* _encoder;
	vRef* vMalloc(int pSize, std::string pType);
	void vFree(vRef* pRef);
	 void desfragmentar();
	static void * hiloEjecucion(void* obj);
	void* control(); //hilo que controla fragmentacion, garbage colector y dump de memoriaa.
	void hiloTotal ();
	pthread_t  tl;



};

#endif /* SRC_VHEAP_H */

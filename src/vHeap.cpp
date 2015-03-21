/*
 * vHeap.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: abrahamon
 */

#include "vHeap.h"

vHeap* vHeap::HEAP = 0;

vHeap::vHeap(int pSize, int pOverweight)
{
	this->memoriaFisica = calloc(1,pSize);
	this->offsetVHeap = 0;
	this->overweight = pOverweight;
	this->size = pSize;
	this->tabla = new xTable();
	this->ColectorDeBasura = new garbageCollector();
	this->zonaCritica = 0;
};


vHeap::~vHeap(){
	free(this->memoriaFisica);
};

vHeap* vHeap::getInstancia()
{
	if( HEAP != 0)
	{
		return HEAP;
	}else{
		HEAP = new vHeap(200,0);

		return HEAP;
	}
};

vRef* vHeap::vMalloc(int pSize, std::string pType)
{

	if(pType == "vInt"){
		//if(size-ptrNextPosicion)
			//cout <<"estoy ingresando un int"<<offsetVHeap<<"\n";
	}
	else if(pType == "vChar"){}
	else if(pType == "vFloat"){}
	else if(pType == "vLong"){}
	else{std::cout <<"vHeap.vMalloc con pType erroneo";};
//	tabla->addEntry(pSize,   , pType);
};

void vHeap::vFree(){};
void vHeap::vFreeAll(){};

void vHeap::dumpMemory()
{

}




/*
 * vHeap.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: abrahamon
 */

#include "vHeap.h"


vHeap::vHeap(int pSize, int pOverweight)
{
	memoriaFisica = calloc(1,pSize);

	this->overweight = pOverweight;
	this->size = pSize;
};

void vHeap::vMalloc(int pSize, std::string pType){};
void vHeap::vFree(){};
void vHeap::vFreeAll(){};

vHeap::~vHeap(){
	free(this->memoriaFisica);
};


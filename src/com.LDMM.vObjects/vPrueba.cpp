/*
 * vPrueba.cpp
 *
 *  Created on: Apr 15, 2015
 *      Author: fabian
 */

#include "vPrueba.h"

vPrueba::vPrueba() {
	pData = 0;
}

vPrueba::~vPrueba() {}

vRef* vPrueba::operator= (const int &s){
	vPrueba* vObj = new (vHeap::getInstancia()->_ptrUltimaMemoriaLibre) vPrueba();
	pData = s;
	return vHeap::getInstancia()->vMalloc(32,Constants::TYPE_INT);

}

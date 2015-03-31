/*
 * vInt.cpp
 *
 *  Created on: 15/3/2015
 *      Author: tvlenin
 */

#include "vInt.h"
#include "../com.LDMM.MemoryManager/vHeap.h"
#include <typeinfo>

void vInt::operator= (const int& s){
	vIntData = s;
	setVObjectData((void*)&vIntData);
	setVObjectType(TYPE_INT);

	cout<<"me invocaron dijo lenin "<< s <<"\n";

	vHeap::HEAP->vWrite(this->_ID,void* s);

	//return ref;
}


 vInt::vInt(){
	vIntData = 0;
}



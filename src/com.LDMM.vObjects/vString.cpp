/*
 * vString.cpp
 *
 *  Created on: 24/3/2015
 *      Author: tvlenin
 */
#include "vString.h"
vRef* vString::operator= (const string& s){
	vStringData = s;
	setVObjectData((void*)&vStringData);
	setVObjectType(Constants::TYPE_STRING);
	return vHeap::getInstancia()->vMalloc(1,Constants::TYPE_STRING);
}
 vString::vString(){

}


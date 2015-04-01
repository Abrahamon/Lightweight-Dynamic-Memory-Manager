/*
 * vLong.cpp
 *
 *  Created on: 24/3/2015
 *      Author: tvlenin
 */

#include "vLong.h"

vRef* vLong::operator= (const long& s){
	vLongData = s;
	setVObjectData((void*)&vLongData);
	setVObjectType(Constants::TYPE_LONG);
	return vHeap::getInstancia()->vMalloc(40,Constants::TYPE_LONG);
}
 vLong::vLong(){

}




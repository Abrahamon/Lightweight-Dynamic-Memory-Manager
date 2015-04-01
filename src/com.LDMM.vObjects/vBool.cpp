/*
 * vBool.cpp
 *
 *  Created on: 25/3/2015
 *      Author: tvlenin
 */

#include "vBool.h"

vRef* vBool::operator= (const bool& s){
	vBoolData = s;
	setVObjectData((void*)&vBoolData);
	setVObjectType(Constants::TYPE_BOOL);
	return vHeap::getInstancia()->vMalloc(32,Constants::TYPE_BOOL);;
}
 vBool::vBool(){

}




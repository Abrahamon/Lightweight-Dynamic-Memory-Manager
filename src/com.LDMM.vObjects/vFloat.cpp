/*
 * vFloat.cpp
 *
 *  Created on: 24/3/2015
 *      Author: tvlenin
 */

#include "vFloat.h"

vRef* vFloat::operator= (const float& s){
	vFloatData = s;
	setVObjectData((void*)&vFloatData);
	setVObjectType(Constants::TYPE_FLOAT);
	return vHeap::getInstancia()->vMalloc(1,Constants::TYPE_FLOAT);
}
 vFloat::vFloat(){

}




